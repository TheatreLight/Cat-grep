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
    int isPattern = 0;
    tNode *tmp = NULL;
    char *temp = (char *)calloc(1024, sizeof(char));
    char **pattern_arr = (char **)calloc(100, sizeof(char *));
    for (int p = 0; p < 100; p++) {
        pattern_arr[p] = (char *)calloc(100, sizeof(char));
    }
    regmatch_t *match = (regmatch_t *)malloc(1024 * sizeof(regmatch_t));
    for (int i = flag.e_count + 1; i < argc; i++) {
        char *str = argv[i];
        int isOneFile;
        if (str[0] != '-' && isPattern == 0) {
            if (flag.e_count > 1 && !flag.f) {  // if the patterns counter more then 1 push pattern into stack
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
            tmp = *list;  // we have to memorize start address of patterns list
            isPattern = 1;
            isOneFile = argc - i;
        }
        if (flag.h)
            isOneFile = 1;
        if (isPattern) {  // if we have finised reading patterns begin to read files
            fp = fopen(argv[i], "r");
            if (!fp) {
                if (!flag.s) printf("s21_grep: %s: No such file or directory\n", argv[i]);
                continue;
            }
            int string_num = 1;
            while (fgetc(fp) != EOF) {
                fseek(fp, -1, SEEK_CUR);
                fgets(temp, 1024, fp);
                *list = tmp;  // the pointer has returned to start address
                char *value = get_value(list);
                int check_exec = 0;
                while (value) {
                    if (flag.i)
                        regcomp(&regex, value, REG_ICASE);
                    else
                        regcomp(&regex, value, 0);
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
                        check_exec = regexec(&regex, temp, 0, NULL, 0);
                        if (!check_exec && !flag.v)
                            count++;
                        regfree(&regex);
                    }
                    if (!check_exec && flag.l) break;
                    if (!check_exec && !flag.v && !flag.o && !flag.c) {
                        print_overlap(argv[i], temp, flag.n, string_num, isOneFile);
                        break;
                    }
                    value = get_value(list);
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
    *list = tmp;  // return the pointer again to start of the list to remove that list
    deleteList(list);
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
