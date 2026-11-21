CXX     = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

.PHONY: all clean oop oop-run oop-format

all: oop

oop: main

main: src/main.cpp src/list.cpp src/list.h
	$(CXX) $(CXXFLAGS) -o $@ src/main.cpp src/list.cpp

oop-run: main
	./main

oop-format:
	clang-format -i src/main.cpp src/list.cpp src/list.h

clean:
	rm -f main
