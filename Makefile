CC      = gcc
CFLAGS  = -Wall -Wextra

.PHONY: all lab2 lab2-run lab2-format clean

all: lab2

lab2: lab2.out

lab2.out: lab2/src/main.c lab2/src/list.c lab2/src/list.h
	$(CC) $(CFLAGS) -o $@ lab2/src/main.c lab2/src/list.c

lab2-run: lab2.out
	./lab2.out

lab2-format:
	clang-format -i lab2/src/main.c lab2/src/list.h lab2/src/list.c

clean:
	rm -f *.out
