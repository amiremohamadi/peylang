%language "c++"
%defines
%define api.namespace {pey}
%define parser_class_name {Parser}
%error-verbose


%{
#include <iostream>
#include <list>

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

%right '='
%left '+' '-'
%left '*' '/'

%type<std::list<Statement>> statements
%type<Statement> statement
%type<Statement> assignment
%type<Statement> print 
%type<Expression> expression


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
          | T_FLOAT64 { /* do something */ }
          | T_IDENT { /* do something */ }
          | expression '+' expression { /* do something*/ }
          | expression '-' expression { /* do something */ }
          | expression '*' expression { /* do something */ }
          | expression '/' expression { /* do something */ }
;
%%
