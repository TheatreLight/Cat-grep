#include <getopt.h>
#include <stdio.h>
#include "parcer.h"

struct Bool parcer(int argc, char **argv, struct Bool flags) {
    const char *sh_opts = "bEtTeivclnhsfo";
    const struct option l_opts[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
    };
    char key = ' ';
    while ((key = getopt_long(argc, argv, sh_opts, l_opts, NULL)) != -1) {
        flags = set_b(flags, key);
        flags = set_up_e(flags, key);
        flags = set_t(flags, key);
        flags = set_up_t(flags, key);
        flags = set_e(flags, key);
        flags = set_i(flags, key);
        flags = set_v(flags, key);
        flags = set_c(flags, key);
        flags = set_l(flags, key);
        flags = set_n(flags, key);
        flags = set_h(flags, key);
        flags = set_s(flags, key);
        flags = set_f(flags, key);
        flags = set_o(flags, key);
        flags = set_unknown(flags, key);
    }
    return flags;
}

struct Bool set_b(struct Bool flags, char ch) {
    if (ch == 'b') flags.b = TRUE_;
    return flags;
}

struct Bool set_up_e(struct Bool flags, char ch) {
    if (ch == 'E') flags.E = TRUE_;
    return flags;
}

struct Bool set_t(struct Bool flags, char ch) {
    if (ch == 't') flags.t = TRUE_;
    return flags;
}

struct Bool set_up_t(struct Bool flags, char ch) {
    if (ch == 'T') flags.T = TRUE_;
    return flags;
}

struct Bool set_e(struct Bool flags, char ch) {
    if (ch == 'e') {
        flags.e = TRUE_;
        flags.e_count++;
    }
    return flags;
}

struct Bool set_i(struct Bool flags, char ch) {
    if (ch == 'i') flags.i = TRUE_;
    return flags;
}

struct Bool set_v(struct Bool flags, char ch) {
    if (ch == 'v') flags.v = TRUE_;
    return flags;
}

struct Bool set_c(struct Bool flags, char ch) {
    if (ch == 'c') flags.c = TRUE_;
    return flags;
}

struct Bool set_l(struct Bool flags, char ch) {
    if (ch == 'l') flags.l = TRUE_;
    return flags;
}

struct Bool set_n(struct Bool flags, char ch) {
    if (ch == 'n') flags.n = TRUE_;
    return flags;
}

struct Bool set_h(struct Bool flags, char ch) {
    if (ch == 'h') flags.h = TRUE_;
    return flags;
}

struct Bool set_s(struct Bool flags, char ch) {
    if (ch == 's') flags.s = TRUE_;
    return flags;
}

struct Bool set_f(struct Bool flags, char ch) {
    if (ch == 'f') flags.f = TRUE_;
    return flags;
}

struct Bool set_o(struct Bool flags, char ch) {
    if (ch == 'o') flags.o = TRUE_;
    return flags;
}

struct Bool set_unknown(struct Bool flags, char ch) {
    if (ch == ' ') flags.unknown = TRUE_;
    return flags;
}