#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include "../common/parcer.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef struct Node {
    struct Node *next;
    char *data;
} tNode;

void grep(int, char**, FILE*, tNode**, struct Bool);
void GetPatternsSet(FILE*, tNode**, struct Bool, char**, int, char**, int*);
void PatternsFileReader(FILE*, struct Bool, tNode**, char*);
int PatternsLineReader(int, tNode**, char**, int);

int GetMatches(char*, tNode**, struct Bool, int*, char*, int, char*, int, int);
void OnlyMatchingFind(regex_t*, char*, char*, struct Bool, int c, int f);
void PrintLineWithMatch(char*, char*, int, int, int);

int IsPatternsLine(char, int);
void push(tNode**, char*);
char* get_value(tNode**);
void DeleteStack(tNode**);

#endif  // SRC_GREP_S21_GREP_H_

