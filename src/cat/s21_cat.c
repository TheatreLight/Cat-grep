#include <stdio.h>
#include <getopt.h>
#include "s21_cat.h"
#include "../common/parcer.h"

int main(int argc, char**argv) {
    FILE *fp = NULL;
    struct Bool flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool current_flags = parcer(argc, argv, flags);
    cat(fp, argc, argv, current_flags);
    return 0;
}

void cat(FILE *fp, int argc, char **argv, struct Bool flag) {
    if (flag.unknown) return;
    for (int i = 1; i < argc; ++i) {
        char *str = argv[i];
        if (is_filename(str[0])) {
            fp = fopen(argv[i], "r");
            stream_handler(fp, flag);
            fclose(fp);
        }
    }
}

void stream_handler(FILE* fp, struct Bool flags) {
    char ch;
    int is_new_line = TRUE_;
    int not_empty_count = 1;
    int newline_count = 1;
    int empty_count = 1;
    while ((ch = fgetc(fp)) != EOF) {
        if (flags.s) {
            if ((empty_count = squeeze_empty(empty_count, ch)) >= 3) continue;
        }
        if (flags.b) {
            not_empty_count = not_empty_line_number(&is_new_line, not_empty_count, ch);
        } else if (flags.n) {
            newline_count = new_line_number(&is_new_line, newline_count, ch);
        }
        if (flags.t) {
            nonprint_symbols(ch, flags);
        }
        if (flags.T && !flags.t) {
            if (ch == 9) {
                nonprint_symbols(ch, flags);
                continue;
            }
        }
        if (flags.e && !flags.t) {
            nonprint_symbols(ch, flags);
        }
        if (flags.E && !flags.e) {
            nonprint_symbols(ch, flags);
        }
        if (!flags.t && !flags.e) {
            putchar(ch);
        }
    }
}

int new_line_number(int* is_new_line, int n, char ch) {
    if (*is_new_line) {
        printf("%6d\t", n);
        n++;
    }
    *is_new_line = check_newline(ch);
    return n;
}

int not_empty_line_number(int* is_new_line, int b, char ch) {
    if (ch != '\n' && *is_new_line) {
        printf("%6d\t", b);
        b++;
    }
    *is_new_line = check_newline(ch);
    return b;
}

int squeeze_empty(int empty_count, char ch) {
    if (ch == '\n') empty_count++;
    else empty_count = 0;
    return empty_count;
}

void nonprint_symbols(char ch, struct Bool flags) {
    if (is_esc_symbols(ch, flags)) {
        putchar('^');
        putchar(ch + 64);
    } else if (is_del_symbol(ch, flags)) {
        putchar('^');
        putchar(63);
    } else if (is_tab_symbol(ch, flags)) {
        putchar('^');
        putchar('I');
    } else if (is_newline_symbol(ch, flags)) {
        putchar('$');
        if (flags.e)
            putchar('\n');
    } else if (!flags.T && !flags.E) {
        putchar(ch);
    }
}

int check_newline(char ch) {
    return ch == '\n';
}

int is_filename(char ch) {
    return ch != '-';
}

int is_esc_symbols(char ch, struct Bool flags) {
    return (ch < 9 || ch > 10) && ch < 32 && (flags.t || flags.e);
}

int is_del_symbol(char ch, struct Bool flags) {
    return ch == 127 && (flags.t || flags.e);
}

int is_tab_symbol(char ch, struct Bool flags) {
    return ch == 9 && (flags.t || flags.T);
}

int is_newline_symbol(char ch, struct Bool flags) {
    return ch == 10 && (flags.e || flags.E);
}