#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
struct flags {
  int b, e, n, s, t, v, E, T, uncorrect;
};
struct flags parsing_flags(struct flags flags, char *word, unsigned int k);
int detect_needs_in_order(char arr[N]);
void numeration(int *c);
void print_str_with_b(char arr[N], int *c);
void printf_str(char arr[N], struct flags flags, int counter_strings);
void print_str_with_s(char arr[N], int *collapse, struct flags flags, int c);
void open_file(char *name, struct flags flags);

int main(int argc, char *argv[]) {
  struct flags flags={0};
  int num = argc;
  for (int i = 1; i < num; i++) {
    for (unsigned int j = 0; j < strlen(argv[i]); j++) {
      if (!j && argv[i][j] == '-' && j < strlen(argv[i]) - 1) {
        flags = parsing_flags(flags, argv[i], ++j);
        j = strlen(argv[i]);
        continue;
      } else if (!flags.uncorrect) {
        open_file(argv[i], flags);
        j = strlen(argv[i]);
      }
    }
  }
  if (flags.uncorrect)
    fprintf(stderr, "Uncorrect flag\n");
  return 0;
}
struct flags parsing_flags(struct flags flags, char *word, unsigned int k) {
  int l = strlen(word);
  for (int j = k; j < l && !flags.uncorrect; j++) {
    if (word[j] == 'b') {
      flags.b = 1;
      continue;
    }
    if (word[j] == 'e') {
      flags.e = 1;
      flags.v = 1;
      continue;
    }
    if (word[j] == 'n') {
      flags.n = 1;
      continue;
    }
    if (word[j] == 's') {
      flags.s = 1;
      continue;
    }
    if (word[j] == 't') {
      flags.t = 1;
      flags.v = 1;
      continue;
    }
    if (word[j] == 'v') {
      flags.v = 1;
      continue;
    }
    if (word[j] == 'T') {
      flags.T = 1;
      continue;
    }
    if (word[j] == 'E') {
      flags.E = 1;
      continue;
    }
    flags.uncorrect = 1;
  }
  return flags;
}
void open_file(char *name, struct flags flags) {
  FILE *file = fopen(name, "r");
  if (!file) {
    fprintf(stderr, "Error file\n");
  } else {
    int c = 1, j = 0, collapse = 0, inner_counter = 0, counter_strings = 1;
    char ARR[N], arr[N];
    while ((ARR[j] = fgetc(file)) != EOF) {
      if (ARR[j] == '\n') {
        counter_strings++;
        j = 0;
      }
      j++;
    }
    fclose(file);
    FILE *file = fopen(name, "r");
    while (fgets(arr, N, file)) {
      inner_counter++;
      if (inner_counter == counter_strings)
        counter_strings = 1;
      if (flags.b) {
        if (!collapse || strlen(arr) > 1 || (strlen(arr) == 1 && arr[0] != 10))
          print_str_with_b(arr, &c);
        if (!flags.s)
          printf_str(arr, flags, counter_strings);
        else
          print_str_with_s(arr, &collapse, flags, counter_strings);
        continue;
      } else if (flags.n) {
        if (!collapse || detect_needs_in_order(arr))
          numeration(&c);
        if (!flags.s)
          printf_str(arr, flags, counter_strings);
        else
          print_str_with_s(arr, &collapse, flags, counter_strings);
        continue;
      } else if (flags.s) {
        print_str_with_s(arr, &collapse, flags, counter_strings);
        continue;
      }
      printf_str(arr, flags, counter_strings);
    }
    fclose(file);
  }
}
int detect_needs_in_order(char arr[N]) {
  int need = 0;
  unsigned int i = 0;
  while (i < strlen(arr) && arr[i] != 10) {
    i++;
  }
  if (i > 1 || (i == 1 && arr[i - 1] != '\n'))
    need = 1;
  return need;
}
void print_str_with_b(char arr[N], int *c) {
  int need = detect_needs_in_order(arr);
  if (need)
    numeration(c);
}
void numeration(int *c) {
  int a = *c, len = 0;
  while (a > 0) {
    a /= 10;
    len++;
  }
  while ((6 - len) > 0) {
    printf(" ");
    len++;
  }
  printf("%d\t", (*c)++);
}
void printf_str(char arr[N], struct flags flags, int counter_strings) {
  for (unsigned int i = 0; (counter_strings != 1 && arr[i] != '\n') ||
                           (counter_strings == 1 && arr[i]);
       i++) {
    if (flags.v &&
        (arr[i] >= 0 && arr[i] < 32 && arr[i] != 9 && arr[i] != 10)) {
      printf("^%c", arr[i] + 64);
    } else if (flags.t == 1 && (arr[i] == 9)) {
      printf("^%c", 'I');
    } else if ((arr[i] == 127) && flags.v == 1) {
      printf("^%c", arr[i] - 64);
    } else {
      printf("%c", arr[i]);
    }
  }
  if (flags.e) {
    if (counter_strings != 1)
      printf("$%c", '\n');
  } else {
    if (counter_strings != 1)
      printf("%c", '\n');
  }
}
void print_str_with_s(char arr[N], int *collapse, struct flags flags, int c) {
  int need = detect_needs_in_order(arr);
  if (need) {
    printf_str(arr, flags, c);
    *collapse = 0;
  } else {
    if (!(*collapse)) {
      printf_str(arr, flags, c);
      *collapse = 1;
    }
  }
}
