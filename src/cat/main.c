#include "s_cat.h"

int main(int argc, char** argv) {
    FILE *fp = NULL;
    struct Bool flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool current_flags = parcer(argc, argv, flags);
    cat(fp, argc, argv, current_flags);
    return 0;
}