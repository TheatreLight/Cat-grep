#include <getopt.h>
#include <stdio.h>
#include "parcer.h"

struct Bool parcer(int argc, char **argv, struct Bool flag) {
    const char *sh_opts = "bEtTeivclnhsfo";
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
            break;

        case 'E':
            flag.E = 1;
            break;

        case 't':
            flag.t = 1;
            break;

        case 'T':
            flag.T = 1;
            break;

        case 'e':
            flag.e = 1;
            flag.e_count++;  // count patterns
            break;

        case 'i':
            flag.i = 1;
            break;

        case 'v':
            flag.v = 1;
            break;

        case 'c':
            flag.c = 1;
            break;

        case 'l':
            flag.l = 1;
            break;

        case 'n':
            flag.n = 1;
            break;

        case 'h':
            flag.h = 1;
            break;

        case 's':
            flag.s = 1;
            break;

        case 'f':
            flag.f = 1;
            break;

        case 'o':
            flag.o = 1;
            break;

        default:
            flag.use_flags = 1;
            break;
        }
    }
    return flag;
}
