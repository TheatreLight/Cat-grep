#include <stdlib.h>
#include "s21_grep.h"

/* Patterns stack functions */
void push(tNode **head, char *string) {
    tNode *tmp = (tNode*)malloc(sizeof(tNode));
    tmp->data = string;
    tmp->next = (*head);
    (*head) = tmp;
}

char* get_value(tNode **head) {
    char *value = NULL;
    if ((*head) != NULL) {
        value = (*head)->data;
        (*head) = (*head)->next;
    }
    return value;
}

void deleteList(tNode **head) {
    tNode* prev = NULL;
    while (*head) {
        prev = (*head)->next;
        free(*head);
        *head = prev;
    }
}
