CC      = gcc
CFLAGS  = -Wall -Wextra

.PHONY: all clean

all: oop

oop: main

main: src/main.c
	$(CC) $(CFLAGS) -o $@ $<

oop-run: main
	./main

oop-format:
	clang-format -i src/main.c

clean:
	rm -f *.out
