CXX 	:= g++
LEX 	:= flex
YACC 	:= bison -d

PROGRAM := peyman

INCLUDE := -Iinclude/ -Iparser/
SRC 	:= $(wildcard peylang/*cc)
OBJ		:= $(SRC:%.cc=%.o) parser/parser.tab.o parser/lex.yy.o


all: $(PROGRAM)

peyman: $(OBJ)
	$(CXX) $(INCLUDE) -o $(PROGRAM) $(OBJ) peyman.cc

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

clean:
	rm -f $(OBJ) $(PROGRAM) parser/parser.tab.c parser/parser.tab.h parser/lex.yy.c

.PHONY: all clean
