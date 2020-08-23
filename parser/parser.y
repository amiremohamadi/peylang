%error-verbose

%code requires {

#include <statement.hh>
#include <expression.hh>
#include <program.hh>

using namespace pey;

}


%{

#include <iostream>

using std::cerr;
using std::endl;


extern int yylex();
extern int yylineno;

bool error = false;

int parse_result = 1;

void yyerror(const char *str) {
    // check error flag to supress duplicate message (actually it's bison stuff)
    if (!error) 
        cerr << "Akh! Khate " << yylineno << " moshkel dare! "
             << str << endl;
}

void yyerror(const char *str, char chr) {
    cerr << "Akh! Khate " << yylineno << " moshkel dare! " 
         << str << "\"" << chr << "\"" << endl;
    // set error flag to be used in yyerror(const char *str) function
    error = true;
}

%}

%union {
    int integer;
    double float64;
    char *ident;
    Expression *exp;
    Statement *stmt;
    StatementList *stmtlist;
    /* ExpressionList *explist; */
}

%token<integer>    P_INT    "integer"
%token<float64>    P_FLOAT  "float64"
%token<ident>      P_IDENT  "ident"
%token             P_CHIZ   "chiz"
%token             P_PRINT  "print"

%type<exp> expression;
%type<stmt> statement;
%type<stmt> assignment;
%type<stmt> print;
%type<stmtlist> statement_list;
/* %type<explist> expression_list; */


%%

program: /**/
       | statement_list { Program($1).eval(); }
;

statement_list: statement_list statement { $1->push_back($2); $$ = $1; }
              | statement { 
                            StatementList *stment_lst = new StatementList; 
                            stment_lst->push_back($1);
                            $$ = stment_lst;
                          }
;

statement: assignment
         | print
;

assignment: P_CHIZ P_IDENT '=' expression {
            $$ = new Assign($2, $4);
            delete [] $2;
          }
;

print: P_PRINT expression { $$ = new Print($2); }
;

expression: P_INT { $$ = new Constant($1); }
          | P_IDENT {
                        $$ = new Identifier($1);
                        delete [] $1;
                    }
; 

%%
