#include "s21_grep.h"

int main(int argc, char **argv) {
    FILE *fp = NULL;
    tNode *patternList = NULL;
    struct Bool flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct Bool result_flags = parcer(argc, argv, flags);
    grep(argc, argv, fp, &patternList, result_flags);
    return 0;
}
