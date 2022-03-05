#ifndef SRC_COMMON_PARCER_H_
#define SRC_COMMON_PARCER_H_

struct Bool {
    int b;
    int E;
    int t;
    int T;
    int e;
    int e_count;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int use_flags;
};

struct Bool parcer(int argc, char **argv, struct Bool flag);

#endif  // SRC_COMMON_PARCER_H_
