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
        cerr << "MARG! khatt'e " << yylineno << " eshtebahe! "
             << str << endl;
}

void yyerror(const char *str, char chr) {
    cerr << "MARG! khatt'e " << yylineno << " eshtebahe! " 
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
		Program *prog;
    /* ExpressionList *explist; */
}

%token<integer>    P_INT    "integer"
%token<float64>    P_FLOAT  "float64"
%token<ident>      P_IDENT  "ident"
%token             P_CHIZ   "chiz"
%token             P_PRINT  "print"
%token             P_EOL    ";"

%type<exp> expression;
%type<stmt> statement;
%type<stmt> assignment;
%type<stmt> print;
%type<prog> program;
/* %type<stmtlist> statement_list; */
/* %type<explist> expression_list; */


%%

main: /**/
    | program {}
;

program: program statement { $1->exec($2); $$ = $1; }
       | statement { 
                        Program *prog = new Program; 
                        prog->exec($1);
                        $$ = prog;
                    }
;

statement: assignment P_EOL
         | print      P_EOL
;

assignment: P_CHIZ P_IDENT '=' expression {
            $$ = new Assign($2, $4);
            delete [] $2;
          }
;

print: P_PRINT expression { $$ = new Print($2); }
;

expression: 
          '(' expression ')' { $$ = $2; }
          | P_INT   { $$ = new Constant($1); }
          | P_FLOAT { $$ = new Constant($1); }
          | P_IDENT {
                        $$ = new Identifier($1);
                        delete [] $1;
                    }
          | expression '+' expression { $$ = new Sum($1, $3); }
          | expression '-' expression { $$ = new Sub($1, $3); }
          | expression '*' expression { $$ = new Mul($1, $3); }
          | expression '/' expression { $$ = new Div($1, $3); }
; 

%%
