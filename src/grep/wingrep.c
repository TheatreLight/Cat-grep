#include "wingrep.h"

void grep(int argc, char **argv, FILE *fp, tNode **stack, struct Bool flags) {
    int is_pattern = TRUE_;
    tNode *start_address = NULL;
    char *founded_match = (char *)calloc(1024, sizeof(char));
    int file_count = 0;
    for (int i = flags.e_count + 1; i < argc; i++) {
      if (IsPatternsLine(argv[i][0], is_pattern)) {
        if (!flags.f) {
          i = PatternsLineReader(flags.e_count, stack, argv, i);
        } else {
          PatternsFileReader(fp, flags, stack, argv[i]);
          i++;
        }
        start_address = *stack;
        is_pattern = FALSE_;
        file_count = argc - i;
      }
      if (flags.h) file_count = 1;
      if (!is_pattern) {
        int match_count = 0;
        fp = fopen(argv[i], "r");
        if (!fp) {
          if (!flags.s) printf("s21_grep: %s: No such file or directory\n", argv[i]);
            continue;
        }
      int line_number = 1;
      while (fgetc(fp) != EOF) {
        fseek(fp, -1, SEEK_CUR);
        fgets(founded_match, 1024, fp);
        *stack = start_address;
        char *value = get_value(stack);
        int is_match_found = GetMatches(value, stack, flags, &match_count, 
                        founded_match, line_number, argv[i], file_count, is_match_found);
        if (is_match_found && flags.v) {
          if (!flags.c) {
            PrintLineWithMatch(argv[i], founded_match, flags.n, line_number, file_count);
          }
          match_count++;
        }
        if (!is_match_found && flags.l) {
          printf("%s\n", argv[i]);
          break;
        }
        line_number++;
      }
      if (flags.c && !flags.l) {
        if (file_count > 1) printf("%s:", argv[i]);
          printf("%d\n", match_count);
      }
      fclose(fp);
    }
  }
  *stack = start_address;
  DeleteStack(stack);
  free(founded_match);
}

int GetMatches(char* value, tNode** stack, struct Bool flags, int *match_count, 
              char* founded_match, int line_number, char* line, int file_count, int is_match_found) {
  regex_t regex;
  is_match_found = FALSE_;
  while (value) {
    if (flags.i)
      regcomp(&regex, value, REG_ICASE);
    else
      regcomp(&regex, value, 0);
    if (flags.o && !flags.l && !flags.c) {
      OnlyMatchingFind(&regex, line, founded_match, flags, line_number, file_count);
    } else {
      is_match_found = regexec(&regex, founded_match, 0, NULL, 0);
    }
    if (!is_match_found && !flags.v) 
      (*match_count)++;
    regfree(&regex);
    if (!is_match_found && flags.l) break;
    if (!is_match_found && !flags.v && !flags.o && !flags.c) {
      PrintLineWithMatch(line, founded_match, flags.n, line_number, file_count);
      break;
    }
    value = get_value(stack);
    if (!is_match_found && flags.v) break;
  }
  return is_match_found;
}

void GetPatternsSet(FILE* fp, tNode** stack, struct Bool flags, char** line, 
                    int is_file, char** patterns_set, int *i) {
  if (!is_file) {
    *i = PatternsLineReader(flags.e_count, stack, line, *i);
  } else {
    PatternsFileReader(fp, flags, stack, line[*i]);
    *i++;
  }
}

int PatternsLineReader(int patterns_number, tNode** stack, char** pattern, int counter) {
  if (patterns_number >= 1) {
    for (int j = 0; j < patterns_number; ++j) {
      push(stack, pattern[counter]);
      counter++;
    }
  } else if (patterns_number == 0) {
    push(stack, pattern[counter]);
    counter++;
  }
  return counter;
}

void PatternsFileReader(FILE *fp, struct Bool flag, tNode **stack, char *argv) {
  fp = fopen(argv, "r");
  if (!fp) {
    if (!flag.s) printf("s21_grep: %s: No such file or directory\n", argv);
    exit(1);
  }
  int j = 0;
  char **patterns_set = (char **)calloc(10, sizeof(char *));
  for (int p = 0; p < 10; p++) {
    patterns_set[p] = (char *)calloc(100, sizeof(char));
  }
  while (fgetc(fp) != EOF) {
    fseek(fp, -1, SEEK_CUR);
    int k = 0;
    char ch;
    while ((ch = fgetc(fp)) != '\n') {
      patterns_set[j][k] = ch;
      k++;
    }
    push(stack, patterns_set[j]);
    j++;
  }
  fclose(fp);
}

int IsPatternsLine(char ch, int flag) {
  return ch != '-' && flag;
}

void OnlyMatchingFind(regex_t *regex, char *argv, char *founded_match, struct Bool flags, int c, int f) {
  regmatch_t *match = (regmatch_t *)malloc(1024 * sizeof(regmatch_t));
  char *s = founded_match;
  regoff_t len;
  while (1) {
    if (regexec(regex, s, 1024, match, 0)) break;
    len = match[0].rm_eo - match[0].rm_so;
    if (f > 1) printf("%s:", argv);
    if (flags.n) printf("%d:", c);
    printf("%.*s\n", (int)len, s + match[0].rm_so);
    s += match[0].rm_eo;
  }
  free(match);
}

void PrintLineWithMatch(char *argv, char *founded_match, int n, int line_number, int file_count) {
  if (file_count > 1)
    printf("%s:", argv);
  if (n)
    printf("%d:", line_number);
  printf("%s", founded_match);
}
