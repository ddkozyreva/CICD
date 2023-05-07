CFLAG = -Wall -Wextra -Werror -std=c11

all: build test

s21_cat.o: s21_cat.c
	gcc $(CFLAG) -c s21_cat.c

build: s21_cat.o
	gcc $(CFLAG) s21_cat.o -o s21_cat

test: build
	sh cat.sh

clean:
	rm -rf *.o s21_cat

rebuild: clean all