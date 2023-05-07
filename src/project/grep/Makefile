CFLAG = -Wall -Wextra -Werror -std=c11

all: build test

s21_grep.o: s21_grep.c
	gcc $(CFLAG) -c s21_grep.c

build: s21_grep.o
	gcc $(CFLAG) s21_grep.o -o s21_grep

test: build
	sh grep.sh

clean:
	rm -rf *.o s21_grep

rebuild: clean all