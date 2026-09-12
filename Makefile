CC      = gcc
CFLAGS  = -Wall -Wextra

.PHONY: all lab1 lab1-run lab1-format lab2 lab2-run lab2-format lab3 lab3-run lab3-format clean

all: lab1 lab2 lab3

lab1: lab1.out

lab1.out: lab1/src/main.c
	$(CC) $(CFLAGS) -o $@ $<

lab1-run: lab1.out
	./lab1.out

lab1-format:
	clang-format -i lab1/src/main.c

clean:
	rm -f *.out
