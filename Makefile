CC      = gcc
CFLAGS  = -Wall -Wextra

.PHONY: all clean oop-run oop-format

all: oop

oop: main

main: src/main.c src/list.c src/list.h
	$(CC) $(CFLAGS) -o $@ src/main.c src/list.c

oop-run: main
	./main

oop-format:
	clang-format -i src/main.c src/list.c src/list.h

clean:
	rm main