#include <stdio.h>
#include <regex.h>
#include "../common/parcer.h"

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

typedef struct Node {
    struct Node *next;
    char *data;
} tNode;

void print_grep(int argc, char **argv, FILE *fp, tNode **list, struct Bool flag);
void patternFileRead(FILE *fp, struct Bool flag, tNode **list, char *argv, char **pattern_arr);
void o_flag(regex_t *regex, regmatch_t *match, char *argv, char *temp, int n, int c, int f);
void print_overlap(char *argv, char *temp, int n, int string_num, int isOneFile);

void push(tNode **head, char *string);
char* get_value(tNode **head);
void deleteList(tNode **head);

#endif  // SRC_GREP_S21_GREP_H_

