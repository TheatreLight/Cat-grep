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

/* Apply parameters and output them to STDOUT */

void printer(FILE *fp, int argc, char **argv, struct Bool flag) {
    char ch;
    for (int i = 1; i < argc; i++) {
        if (flag.use_flags)  // break the loop if we have unknown parameter
            break;
        char *str = argv[i];
        if (str[0] != '-') {  // check if it just a parameters string or a filename already
            char old = '\n';    // this char we need for numeration of a new line
            int b = 1;  // the line counter
            int n = 1;  // the simple counter
            fp = fopen(argv[i], "r");
            while ((ch = fgetc(fp)) != EOF) {  // read the file per character
                if (flag.s) {
                    static int s = 1;
                    if (ch == '\n') {  // looking for an empty line
                        s++;
                    if (s >= 3)  // if three and more line breaks detected
                        continue;  // it mean duplicating of empty string, skip it
                    } else {
                        s = 0;  // if it not detected skip the counter to zero
                    }
                }
                if (flag.b) {
                    static int b_found = 1;  // line that must be numbered has detected
                    if (ch == '\n')  // found the line break
                        b_found++;
                    if (ch != '\n' && b_found > 0) {  // if another line doeasn't start from \n
                            printf("%6d\t", b);  // but line break has memorized already, number the line
                        b++;  // increase the counter
                        b_found = 0;  // skip flag to zero 
                    }
                    } else if (flag.n) {  // numbering lines one by one if turned off numbering not-empty lines
                        if (old == '\n') {
                                printf("%6d\t", n);
                            n++;
                        }
                        old = ch;
                    }
                if (flag.t) {  // special function for print nonprintig symbols
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (flag.T && !flag.t) {
                    if (ch == 9) {
                        nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                        continue;
                    }
                }
                if (flag.e && !flag.t) {
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (flag.E && !flag.e) {
                    nonprint_printer(ch, flag.t, flag.e, flag.T, flag.E);
                }
                if (!flag.t && !flag.e) {
                    putchar(ch);  // and then we output all another information which has not been edited
                }
            }
        fclose(fp);
        }
    }
}

/* non-printing symbols printer */

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
