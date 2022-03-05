#include <stdio.h>
#include <getopt.h>
#include "s21_cat.h"
#include "../common/parcer.h"

int main(int argc, char**argv) {
    FILE *fp = NULL;
    struct Bool flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool result_flag = parcer(argc, argv, flag);
    printer(fp, argc, argv, result_flag);
    return 0;
}

/* А здесь применение параметров и вывод их в консоль */

void printer(FILE *fp, int argc, char **argv, struct Bool flag) {
    char ch;  // временный чар, через который символы выводятся в консоль
    for (int i = 1; i < argc; i++) {  // цикл по аргументам, если файлов несколько
        if (flag.use_flags)  // ломаем цикл, если попадается неопределенный параметр
            break;
        char *str = argv[i];
        if (str[0] != '-') {  // проверяем, это уже имя файла или еще строка параметров
            char old = '\n';    // этот чар пригодится для нумерации новой строки ;-))
            int b = 1;  // счетчик строк
            int n = 1;  // счетчик
            fp = fopen(argv[i], "r");
            while ((ch = fgetc(fp)) != EOF) {  // читаем файл посимвольно
                if (flag.s) {
                    static int s = 1;
                    if (ch == '\n') {  // ищем пустую строку
                        s++;
                    if (s >= 3)  // если наблюдаем три и более переноса строки подряд - значит,
                        continue;  // пустая строка дублируется, пропускаем ее
                    } else {
                        s = 0;  // ели же нет - обнуляем счетчик
                    }
                }
                if (flag.b) {
                    static int b_found = 1;  // флаг, что найдена строка подлежащая нумерации
                    if (ch == '\n')  // ищем перенос строки, фиксируем
                        b_found++;
                    if (ch != '\n' && b_found > 0) {  // если очередная строка начинается не с переноса,
                            printf("%6d\t", b);  // но перенос был уже зафиксирован в прошлом, нумеруем ее
                        b++;  // увеличиваем счетчик строк
                        b_found = 0;  // обнуляем флаг
                    }
                    } else if (flag.n) {  // нумерация строк подряд, если отключена нумерация непустых строк
                        if (old == '\n') {  // здесь пригодился заранее заготовленный чар
                                printf("%6d\t", n);  // если он - '\n', значит сейчас новая строка
                            n++;  // увеличиваем счетчик
                        }
                        old = ch;  // перезаписываем чар
                    }
                if (flag.t) {  // спецфункция для печетания непечатного ;-))
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (flag.T && !flag.t) {
                    if (ch == 9) {
                        nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                        continue;  // маленькая хитрость
                    }
                }
                if (flag.e && !flag.t) {
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (flag.E && !flag.e) {
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (!flag.t && !flag.e) {
                    putchar(ch);  // а тут выводим всю остальную информацию из файла
                }
            }
        fclose(fp);
        }
    }
}

/* принтер для непечатаемых символов */

void nonprint_printer(char ch, int flag_t, int flag_e, int flag_T, int flag_E) {
    if ((ch < 9 || ch > 10) && ch < 32 && (flag_t || flag_e)) {
        putchar('^');
        putchar(ch + 64);
    } else if (ch == 127 && (flag_t || flag_e)) {
        putchar('^');
        putchar(63);
    } else if (ch == 9 && (flag_t || flag_T)) {
        putchar('^');
        putchar('I');
    } else if (ch == 10 && (flag_e || flag_E)) {
        putchar('$');
        if (flag_e)
            putchar('\n');
    } else if (!flag_T && !flag_E) {
        putchar(ch);
    }
}
