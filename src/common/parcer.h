#ifndef SRC_COMMON_PARCER_H_
#define SRC_COMMON_PARCER_H_

#define TRUE_ 1
#define FALSE_ 0

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
    int unknown;
};

struct Bool parcer(int, char**, struct Bool);
struct Bool set_b(struct Bool, char);
struct Bool set_up_e(struct Bool, char);
struct Bool set_t(struct Bool, char);
struct Bool set_up_t(struct Bool, char);
struct Bool set_e(struct Bool, char);
struct Bool set_i(struct Bool, char);
struct Bool set_v(struct Bool, char);
struct Bool set_c(struct Bool, char);
struct Bool set_l(struct Bool, char);
struct Bool set_n(struct Bool, char);
struct Bool set_h(struct Bool, char);
struct Bool set_s(struct Bool, char);
struct Bool set_f(struct Bool, char);
struct Bool set_o(struct Bool, char);
struct Bool set_unknown(struct Bool, char);

#endif  // SRC_COMMON_PARCER_H_
