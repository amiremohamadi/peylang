%language "c++"
%defines
%define api.namespace {pey}
%define parser_class_name {Parser}
%error-verbose


%{
#include <iostream>

extern int yylex();
extern int yylineno;

bool error = false;

void yyerror(const char *str) {
    if (!error)
        std::cerr << "error happened at line " << yylineno << " " << str << "\n";
}
%}


%token               T_EOF 0 "end of file"
%token               T_PRINT "print"
%token <std::string> T_IDENT
%token <int>         T_INT;
%token <double>      T_FLOAT64
%token <std::string> T_STRING

%left '+' '-'
%left '*' '/'


%%
program: /* empty */
       | statements { /* do something */  }
;

statements: statements statement { /* do something */ }
          | statement { /* do something */ }
;

statement: assignment
         | print
;

assignment: T_IDENT '=' expression { /* do something */ }
;

print: T_PRINT expression { /* do something */ }
;

expression: '(' expression ')' { /* do something */ }
          | T_INT { /* do something*/ }
          | T_FLOAT64 { /* do something */ }
          | T_IDENT { /* do something */ }
          | expression '+' expression { /* do something*/ }
          | expression '-' expression { /* do something */ }
          | expression '*' expression { /* do something */ }
          | expression '/' expression { /* do something */ }
;
%%
