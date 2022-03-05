#include <stdio.h>
#include <string.h>
#include <getopt.h>
//#include "s21_cat.h"

int main(int argc, char **argv) {
    FILE *fp = NULL;
    char temp[1024] = {'\0'};
    struct Bool flag = {0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool result_flags = parcer(argc, argv, flag);
    printer(fp, argc, argv, temp, result_flags);
    return 0;
}

struct Bool parcer(int argc, char **argv, struct Bool flag) {
    const char* sh_opts = "beEnstT";
    const struct option l_opts[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
    };
    int rez = 0;
    while ((rez = getopt_long(argc, argv, sh_opts, l_opts, NULL)) != -1) {
        switch (rez) {
            case 'b':
            flag.b = 1;
            flag.use_flags = 1;
                break;

            case 'e':
            flag.e = 1;
            flag.use_flags = 1;
            break;

            case 'E':
            flag.E = 1;
            flag.use_flags = 1;
            break;

            case 'n':
            flag.n = 1;
            flag.use_flags = 1;
            break;

            case 's':
            flag.s = 1;
            flag.use_flags = 1;
            break;

            case 't':
            flag.t = 1;
            flag.use_flags = 1;
            break;

            case 'T':
            flag.T = 1;
            flag.use_flags = 1;
            break;

            default:
                break;
        }
    }
    return flag;
}

void printer(FILE *fp, int argc, char **argv, char *temp, struct Bool flag) {
    for (int i = 1; i < argc; i++) {
        char *str = argv[i];
        if (str[0] != '-') {
            fp = fopen(argv[i], "r");
            while (!feof(fp)) {
                fgets(temp, 255, fp);
                char temp_out[1024] = {'\0'};
                if (feof(fp))
                    break;
                app_params(flag, temp, temp_out, fp);
                printf("%s", temp_out);
            }
            fclose(fp);
        }
    }
    
}

void app_params(struct Bool flag, char *temp, char *temp_out, FILE *fp) {
    int x;
    int k = 0;
    char temp_e[1024] = {'\0'};
    if (flag.e) {
        char ch;
        fseek(fp, 0, SEEK_SET);
        while ((ch = fgetc(fp)) != EOF) {
            if ((ch < 9 || ch >10) && ch < 32) {
                temp_e[k] = '^';
                temp_e[k + 1] = ch + 64;
                k += 2;
            } else if (ch == 127) {
                temp_e[k] = '^';
                temp_e[k + 1] = 63;
                k += 2;
            } else if (ch == 10) {
                temp_e[k] = '$';
                temp_e[k + 1] = ch;
                k += 2;
            } else {
                temp_e[k] = ch;
                k++;
            }
        }
    }
    if (flag.s) {
        static int blank_string_count = 0;
            if (temp[0] == '\n')
                blank_string_count++;
            else
                blank_string_count = 0;

            if (blank_string_count >= 2) {

            } else {
                for (int i = 0; i < strlen(temp); i++) {
                    temp_out[i] = temp[i];
                }
            }
    }
    if (flag.b) {
            x = strlen(temp);
            if (k != 0) {
                x = k;
                temp = temp_e;
            }
            if (strlen(temp_out) != 0) {
              x = strlen(temp_out);
              temp = temp_out;
            }
            static int b = 0;
            if ((temp[0] != '\n') && (temp[0] != '$' || temp[1] != '\n')) {
                b++;
                sprintf(temp_out, "     %d  ", b);
            }
            for (int i = 0, j = strlen(temp_out); i < x; i++, j++) {
                if (k != 0) {
                    if ((temp[i] == '\n') && (temp[i+1] != '$' && temp[i+1] != '\0')) {
                        b++;
                        temp_out[j] = temp[i];
                        for (int p = j + 1; p <= j + 5; p++) {
                        temp_out[p] = ' ';
                        if (p == j + 5) {
                            temp_out[p] = b + 48;
                            temp_out[p + 1] = '\t';
                        }
                        }
                        j += 6;
                        x += 7;
                    } else {
                        temp_out[j] = temp[i];
                    }
                } else {
                    temp_out[j] = temp[i];
                }
            }
    } else if (flag.n) {
        x = strlen(temp);
        if (k != 0) {
            x = k;
            temp = temp_e;
        }
        static int count = 1;
        sprintf(temp_out, "    %d\t", count);
        int len = strlen(temp);
        for (int i = 0, j = strlen(temp_out); i < len; i++, j++) {
            if (k != 0) {
                if (temp[i] == '\n') {
                    if (temp[i+1] == '\0')
                        break;
                    temp_out[j] = temp[i];
                    count++;
                    for (int p = j + 1; p <= j + 5; p++) {
                        temp_out[p] = ' ';
                        if (p == j + 5) {
                            temp_out[p] = count + 48;
                            temp_out[p + 1] = '\t';
                        }
                    }
                    j = j + 6;
                    len = len + 7;
                } else {
                    temp_out[j] = temp[i];
                }
            } else {
                if (temp[i] == '\n')
                    count++;
                temp_out[j] = temp[i];
            }
      }
    }
    if (flag.E) {
        if (!flag.e) {
            x = strlen(temp);
            if (strlen(temp_out) != 0) {
                x = strlen(temp_out);
                temp = temp_out;
            }
            for (int i = 0; i < x; i++) {
                if (temp[i] != '\n') {
                    temp_out[i] = temp[i];
                } else {
                    temp_out[i] = '$';
                    temp_out[i + 1] = '\n';
                }
            }
        }
    }
    
    

    if (flag.t) {
      char ch;
      fseek(fp, 0, SEEK_SET);
      while ((ch = fgetc(fp)) != EOF) {
        if ((ch < 9 || ch > 10) && ch < 32) {
          putchar('^');
          putchar(ch + 64);
        } else if (ch == 127) {
          putchar('^');
          putchar(63);
        } else if (ch == 9) {
          putchar('^');
          putchar('I');
        } else {
          putchar(ch);
        }
      }
    }
    if (flag.T) {
      for (int i = 0; i < strlen(temp); i++) {
        if (temp[i] != '\t')
          putchar(temp[i]);
        else
          printf("%c%c", '^', 'I');
      }
    }
}
