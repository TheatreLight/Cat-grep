#ifndef SRC_CAT_S_CAT_H_
#define SRC_CAT_S_CAT_H_

#include "../common/parcer.h"

#include <stdio.h>

void cat(FILE*, int, char**, struct Bool);
void stream_handler(FILE*, struct Bool);
int new_line_number(int*, int, char);
int not_empty_line_number(int*, int, char);
int squeeze_empty(int, char);
void nonprint_symbols(char, struct Bool);
int check_newline(char);
int is_filename(char);
int is_esc_symbols(char, struct Bool);
int is_del_symbol(char, struct Bool);
int is_tab_symbol(char, struct Bool);
int is_newline_symbol(char, struct Bool);

#endif  // SRC_CAT_S_CAT_H_
