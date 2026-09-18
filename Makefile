CC      = gcc
CFLAGS  = -Wall -Wextra

.PHONY: all clean oop-run oop-format

all: oop

oop: main

main: src/main.c src/list.c src/list.h src/subj.h src/subj.c
	$(CC) $(CFLAGS) -o $@ src/main.c src/list.c src/subj.c

oop-run: main
	./main

oop-format:
	clang-format -i src/main.c src/list.c src/list.h src/subj.c src/subj.h

clean:
	rm main