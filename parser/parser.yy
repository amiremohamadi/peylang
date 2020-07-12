%skeleton "lalr1.cc"
%defines
%define api.namespace {pey}
%define parser_class_name {Parser}

%code requires {
#include <expression.hh>
#include <iostream>
#include <string>
#include <list>
#include <object.hh>
#include <program.hh>
#include <statement.hh>
namespace pey {
    class Scanner;
}



// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif


}

%parse-param {Scanner &scanner}

%code{
#include <iostream>
#include <cstdlib>
#include <fstream>

#include <scanner.hh>

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               T_EOF 0 "end of file"
%token               T_PRINT "print"
%token <std::string> T_IDENT
%token <int>         T_INT;
%token <double>      T_FLOAT
%token <std::string> T_STRING

%locations

%right '='
%left '+' '-'
%left '*' '/'

%type<std::list<Statement *>> statements
%type<Statement *> statement
%type<Statement *> assignment
%type<Statement *> print 
%type<Expression *> expression


%%
program: /* empty */
       | statements { Program($1).eval(); }
;

statements: statements statement { $1.push_back($2); }
          | statement { std::list<Statement *> ls; ls.push_back($1);}
;

statement: assignment
         | print
;

assignment: T_IDENT '=' expression { $$ = new Assign($1, $3); }
;

print: T_PRINT expression { $$ = new Print($2); }
;

expression: '(' expression ')' { $$ = $2; }
          | T_INT { /* do something*/ }
          | T_FLOAT { /* do something */ }
          | T_IDENT { /* do something */ }
          | expression '+' expression { /* do something*/ }
          | expression '-' expression { /* do something */ }
          | expression '*' expression { /* do something */ }
          | expression '/' expression { /* do something */ }
;
%%


void pey::Parser::error(const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
