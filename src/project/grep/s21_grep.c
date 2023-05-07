#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 512
struct flags {
  int e, i, v, c, l, n, uncorrect, counter_e, input_e, counter_files;
};
struct flags parsing_flags(struct flags flags, char *flag);
int check_similarities(char *word, char *array_of_words[N], int length);
void insert_words_to_array(char *arr[N], struct flags *flags, char *word);
struct flags parsing_string(char *word, struct flags flags,
                            char *array_of_words[N], char *array_of_files[N]);
void standart_situation(struct flags *flags, char *array_of_words[N],
                        char *array_of_files[N]);
char flags_to_symbol(struct flags *flags);
void printing_strings(char buf_str[N]);
void file_proccessing_e(char *file, char *word, int *stop_flag, int file_flag);
void to_lower(char str[N]);
void file_proccessing_i(char *file, char *word, int *stop_flag, int file_flag);
void file_proccessing_v(char *file, char *word, int *stop_flag, int file_flag);
void file_proccessing_c(char *file, char *word, int *stop_flag, int file_flag);
void file_proccessing_l(char *file, char *word, int *stop_flag);
void file_proccessing_n(char *file, char *word, int *stop_flag, int file_flag);
void case_proccessing(char *file, char *word, int *stop_flag,
                      struct flags *flags);
void proccessing(struct flags *flags, char *array_of_words[N],
                 char *array_of_files[N]);

int main(int argc, char *argv[]) {
  struct flags flags = {0};
  char *array_of_words[N] = {0}, *array_of_files[N] = {0};
  for (int i = 1; i < argc; i++) {
    flags = parsing_string(argv[i], flags, array_of_words, array_of_files);
  }
  if (!flags.uncorrect) {
    standart_situation(&flags, array_of_words, array_of_files);
    proccessing(&flags, array_of_words, array_of_files);
  } else {
    fprintf(stderr, "invalid option --");
  }
  return 0;
}

struct flags parsing_flags(struct flags flags, char *flag) {
  if (flag[1] == 'e') {
    flags.e = 1;
    flags.counter_e++;
    flags.input_e = 1;
  } else if (flag[1] == 'i')
    flags.i = 1;
  else if (flag[1] == 'v')
    flags.v = 1;
  else if (flag[1] == 'c')
    flags.c = 1;
  else if (flag[1] == 'l')
    flags.l = 1;
  else if (flag[1] == 'n')
    flags.n = 1;
  else
    flags.uncorrect = 1;
  return flags;
}

int check_similarities(char *word, char *array_of_words[N], int length) {
  int flag = 1;
  for (int i = 0; i < length && flag; i++) {
    if (!strcmp(array_of_words[i], word)) {
      flag = 0; // if similar
    }
  }
  return flag; // if not similar
}
void insert_words_to_array(char *arr[N], struct flags *flags, char *word) {
  int length = flags->counter_e - 1;
  if (!length || (length && check_similarities(word, arr, length))) {
    arr[length] = word;
  } else {
    flags->counter_e--;
  }
  flags->input_e = 0;
}
struct flags parsing_string(char *word, struct flags flags,
                            char *array_of_words[N], char *array_of_files[N]) {
  if (word[0] == '-') {
    flags = parsing_flags(flags, word);
  } else if (flags.input_e) {
    insert_words_to_array(array_of_words, &flags, word);
  } else {
    array_of_files[flags.counter_files++] = word;
  }
  return flags;
}
void standart_situation(struct flags *flags, char *array_of_words[N],
                        char *array_of_files[N]) {
  if (!flags->counter_e && !(array_of_words[0])) {
    if (flags->counter_files > 1) {
      array_of_words[0] = array_of_files[0];
      flags->counter_e++;
      for (int i = 0; i < flags->counter_files - 1; i++) {
        array_of_files[i] = array_of_files[i + 1];
      }
      flags->counter_files--;
    } else {
      flags->uncorrect = 1;
    }
  }
}
char flags_to_symbol(struct flags *flags) {
  char symbol = '0';
  if (flags->e)
    symbol = 'e';
  else if (flags->i)
    symbol = 'i';
  else if (flags->v)
    symbol = 'v';
  else if (flags->c)
    symbol = 'c';
  else if (flags->l)
    symbol = 'l';
  else if (flags->n)
    symbol = 'n';
  else if (!flags->uncorrect)
    symbol = 'e';
  return symbol;
}
void printing_strings(char buf_str[N]) {
  int c = 0;
  for (int i = 0; buf_str[i]; i++, c++)
    printf("%c", buf_str[i]);
  if (c > 0 && buf_str[--c] != '\n') {
    printf("\n");
  }
}
void file_proccessing_e(char *file, char *word, int *stop_flag, int file_flag) {
  FILE *fp;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    while (fgets(buf_str, N, fp)) {
      if (strstr(buf_str, word)) {
        if (file_flag > 1)
          printf("%s:", file);
        printing_strings(buf_str);
      }
    }
    fclose(fp);
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void to_lower(char str[N]) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}
void file_proccessing_i(char *file, char *word, int *stop_flag, int file_flag) {
  FILE *fp;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    while (fgets(buf_str, N, fp)) {
      char buf_str2[N];
      for (int i = 0; buf_str[i]; i++)
        buf_str2[i] = buf_str[i];
      to_lower(buf_str);
      to_lower(word);
      if (strstr(buf_str, word)) {
        if (file_flag > 1)
          printf("%s:", file);
        int c = 0;
        for (int i = 0; buf_str[i]; i++, c++)
          printf("%c", buf_str2[i]);
        if (c > 0 && buf_str2[--c] != '\n') {
          printf("\n");
        }
      }
    }
    fclose(fp);
  } else {
    printf("grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void file_proccessing_v(char *file, char *word, int *stop_flag, int file_flag) {
  FILE *fp;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    while (fgets(buf_str, N, fp)) {
      if (!strstr(buf_str, word)) {
        if (file_flag > 1)
          printf("%s:", file);
        int c = 0;
        for (int i = 0; buf_str[i]; i++, c++)
          printf("%c", buf_str[i]);
        if (c > 0 && buf_str[--c] != '\n') {
          printf("\n");
        }
      }
    }
    fclose(fp);
  } else {
    printf("grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void file_proccessing_c(char *file, char *word, int *stop_flag, int file_flag) {
  FILE *fp;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    int counter = 0;
    while (fgets(buf_str, N, fp)) {
      if (strstr(buf_str, word)) {
        counter++;
      }
    }
    if (file_flag > 1)
      printf("%s:", file);
    printf("%d\n", counter);
    fclose(fp);
  } else {
    printf("grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void file_proccessing_l(char *file, char *word, int *stop_flag) {
  FILE *fp;
  int stop = 0;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    while (fgets(buf_str, N, fp) && !stop) {
      if (strstr(buf_str, word)) {
        printf("%s\n", file);
        stop = 1;
      }
    }
    fclose(fp);
  } else {
    printf("grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void file_proccessing_n(char *file, char *word, int *stop_flag, int file_flag) {
  FILE *fp;
  char buf_str[N];
  if ((fp = fopen(file, "r"))) {
    int counter = 0;
    while (fgets(buf_str, N, fp)) {
      if (strstr(buf_str, word)) {
        if (file_flag > 1)
          printf("%s:", file);
        printf("%d:", counter + 1);
        printing_strings(buf_str);
      }
      counter++;
    }
    fclose(fp);
  } else {
    printf("grep: %s: No such file or directory\n", file);
    *stop_flag = 0;
  }
}
void case_proccessing(char *file, char *word, int *stop_flag,
                      struct flags *flags) {
  char symbol = flags_to_symbol(flags);
  switch (symbol) {
  case 'e':
    file_proccessing_e(file, word, stop_flag, flags->counter_files);
    break;
  case 'i':
    file_proccessing_i(file, word, stop_flag, flags->counter_files);
    break;
  case 'v':
    file_proccessing_v(file, word, stop_flag, flags->counter_files);
    break;
  case 'c':
    file_proccessing_c(file, word, stop_flag, flags->counter_files);
    break;
  case 'l':
    file_proccessing_l(file, word, stop_flag);
    break;
  case 'n':
    file_proccessing_n(file, word, stop_flag, flags->counter_files);
    break;
  default:
    fprintf(stderr, "error");
  }
}
void proccessing(struct flags *flags, char *array_of_words[N],
                 char *array_of_files[N]) {
  for (int i = 0; i < flags->counter_files; i++) {
    char *file = array_of_files[i];
    if (file) {
      int stop_flag = 1;
      for (int j = 0; j < flags->counter_e && stop_flag; j++) {
        case_proccessing(file, array_of_words[j], &stop_flag, flags);
      }
    }
    file = NULL;
  }
}
