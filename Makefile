CC := g++
CFLAGS := -W -Wall -ansi -std=c++14 -pedantic
SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/prog
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc
run: bin/prog
	bin/prog

.PHONY: clean
OBJFILES := $(wildcard obj/*.o)

clean: $(OBJFILES:obj/%.o=remove_%.o)
	rm -f bin/prog
remove_%.o:
	rm -f obj/$@
