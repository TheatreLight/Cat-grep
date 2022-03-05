#include "s21_grep.h"
#include "../common/parcer.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fp = NULL;
    tNode *patternList = NULL;
    struct Bool flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool result_flags = parcer(argc, argv, flag);
    print_grep(argc, argv, fp, &patternList, result_flags);
    return 0;
}

void print_grep(int argc, char **argv, FILE *fp, tNode **list, struct Bool flag) {
    regex_t regex;
    int count = 0;
    int isPattern = 0;  // Флаг, показывающий закончили уже читать паттерны и перешли к файлам или нет
    tNode *tmp = NULL;  // Заготовленный указатель, понадобится ниже
    char *temp = (char *)calloc(1024, sizeof(char));  // память под считываемую строку из файла
    char **pattern_arr = (char **)calloc(100, sizeof(char *));
    for (int p = 0; p < 100; p++) {
        pattern_arr[p] = (char *)calloc(100, sizeof(char));
    }
    regmatch_t *match = (regmatch_t *)malloc(1024 * sizeof(regmatch_t));
    for (int i = flag.e_count + 1; i < argc; i++) {  // Цикл по аргументам начинаем с количества шаблонов + 1
        char *str = argv[i];  // указатель на текущую строку в массиве строк
        int isOneFile;  // Позже будем проверять, сколько файлов нам надо прочитать
        if (str[0] != '-' && isPattern == 0) {
            if (flag.e_count > 1 && !flag.f) {  // Если счетчик шаблонов больше единицы, складываем в стек
                int j = 0;
                while (j < flag.e_count) {
                    push(list, argv[i]);
                    j++;
                    i++;
                }
            } else if (flag.e_count == 0 && !flag.f) {
                push(list, argv[i]);
                i++;
            } else if (flag.f) {
                patternFileRead(fp, flag, list, argv[i], pattern_arr);
                i++;
            }
            tmp = *list;  // и предусмотрительно записываем адрес начала списка шаблонов!!!
            isPattern = 1;  // опять же, условие надо пересмотреть!!!
            isOneFile = argc - i;  // А вот и проверка на количество файлов
        }
        if (flag.h)
            isOneFile = 1;
        if (isPattern) {  // Если чтение паттернов закончено - приступаем к чтению файлов
            fp = fopen(argv[i], "r");
            if (!fp) {
                if (!flag.s) printf("s21_grep: %s: No such file or directory\n", argv[i]);
                continue;
            }
            int string_num = 1;
            while (fgetc(fp) != EOF) {
                fseek(fp, -1, SEEK_CUR);
                fgets(temp, 1024, fp);
                *list = tmp;  // здесь циклически каждый раз указатель списка возвращается на начало
                char *value = get_value(list);  // тут выдергиваем первое значение из списка
                int check_exec = 0;
                while (value) {  // пока не кончатся значения в списке
                    if (flag.i)
                        regcomp(&regex, value, REG_ICASE);  // игнорируем регистр
                    else
                        regcomp(&regex, value, 0);  // а это типа нормальная компиляция должна быть
                    if (flag.o && !flag.l && !flag.c) {
                        #ifdef __APPLE__
                        if (!regexec(&regex, temp, 1024, match, 0)) {
                            if (isOneFile > 1) printf("%s:", argv[i]);
                            if (flag.n) printf("%d:", string_num);
                        }
                        #endif
                      o_flag(&regex, match, argv[i], temp, flag.n, string_num,
                             isOneFile);
                    } else {
                        check_exec = regexec(&regex, temp, 0, NULL, 0);  // найдены ли совпадения
                        if (!check_exec && !flag.v)
                            count++;
                        regfree(&regex);  // чистим за собой
                    }
                    if (!check_exec && flag.l) break;
                    if (!check_exec && !flag.v && !flag.o && !flag.c) {
                        print_overlap(argv[i], temp, flag.n, string_num, isOneFile);
                        break;
                    }
                    value = get_value(list);  // и дергаем следующее значение из списка
                    if (!check_exec && flag.v) break;
                }
                if (check_exec && flag.v) {
                    if (!flag.c) {
                        print_overlap(argv[i], temp, flag.n, string_num, isOneFile);
                    }
                    count++;
                }
                if (!check_exec && flag.l) {
                    printf("%s\n", argv[i]);
                    break;
                }
                string_num++;
            }
            if (flag.c && !flag.l) {
                if (isOneFile > 1) printf("%s:", argv[i]);
                printf("%d\n", count);
                count = 0;
            }
        fclose(fp);
        }
    }
    *list = tmp;  // опять возвращаем указатель на начало списка, чтоб удалить список
    deleteList(list);  // здесь и далее происходит чистка
    free(temp);
    free(match);
    for (int p = 0; p < 100; p++) {
        free(pattern_arr[p]);
    }
    free(pattern_arr);
}

void patternFileRead(FILE *fp, struct Bool flag, tNode **list, char *argv, char **pattern_arr) {
    fp = fopen(argv, "r");
    if (!fp) {
        if (!flag.s) printf("s21_grep: %s: No such file or directory\n", argv);
        exit(1);
    }
    int j = 0;
    while (fgetc(fp) != EOF) {
        fseek(fp, -1, SEEK_CUR);
        int k = 0;
        char ch;
        while ((ch = fgetc(fp)) != '\n') {
            pattern_arr[j][k] = ch;
            k++;
        }
        push(list, pattern_arr[j]);
        j++;
    }
    fclose(fp);
}

void o_flag(regex_t *regex, regmatch_t *match, char *argv, char *temp, int n, int c, int f) {
    char *s = temp;
    regoff_t len;
    while (1) {
        if (regexec(regex, s, 1024, match, 0)) break;
        len = match[0].rm_eo - match[0].rm_so;
        #ifdef __linux__
        if (f > 1) printf("%s:", argv);
        if (n) printf("%d:", c);
        #endif
        printf("%.*s\n", (int)len, s + match[0].rm_so);
        s += match[0].rm_eo;
    }
}

void print_overlap(char *argv, char *temp, int n, int string_num, int isOneFile) {
    if (isOneFile > 1)
        printf("%s:", argv);
    if (n)
        printf("%d:", string_num);
    printf("%s", temp);
}
