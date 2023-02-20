CXX 	:= g++
FLAGS   := -static -static-libgcc -static-libstdc++

ifeq ($(OS),Windows_NT)
	LEX 	:= win_flex
	YACC 	:= win_bison -d
else
	LEX 	:= flex
	YACC 	:= bison -d
endif

PROGRAM := peyman

INCLUDE := -Iinclude/ -Iparser/
SRC 	:= $(wildcard peylang/object/*cc) $(wildcard peylang/*cc)
OBJ		:= $(SRC:%.cc=%.o) parser/parser.tab.o parser/lex.yy.o


build: $(PROGRAM)

peyman: $(OBJ)
	$(CXX) $(FLAGS) $(INCLUDE) -o $(PROGRAM) $(OBJ) peyman.cc

parser/parser.tab.c: parser/parser.y
	$(YACC) -o parser/parser.tab.c parser/parser.y

parser/parser.tab.o: parser/parser.tab.c
	$(CXX) $(INCLUDE) -c parser/parser.tab.c -o parser/parser.tab.o

parser/lex.yy.c: parser/scanner.l parser/parser.tab.o
	$(LEX) -o parser/lex.yy.c parser/scanner.l

parser/lex.yy.o: parser/lex.yy.c
	$(CXX) $(INCLUDE) -c parser/lex.yy.c -o parser/lex.yy.o

%.o: %.cc
	$(CXX) $(INCLUDE) -c $< -o $@

test: build
	(cat test/integration/cases.text | ( (echo 0 | ./peyman test/integration/tests.pey) | ( diff /dev/fd/3 /dev/fd/4 ) 4<&0 ) 3<&0)

clean:
	rm -f $(OBJ) $(PROGRAM) parser/parser.tab.c parser/parser.tab.h parser/lex.yy.c

.PHONY: build test clean
