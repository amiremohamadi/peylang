%error-verbose

%code requires {

#include <statement.hh>
#include <expression.hh>
#include <program.hh>

using namespace pey;

}


%{

#include <iostream>
#include <cstring>
#include <string>

using std::cerr;
using std::endl;


extern int yylex();
extern int yylineno;

bool error = false;

int parse_result = 1;

void yyerror(const char *str) {
    // check error flag to supress duplicate message (actually it's bison stuff)

    // custom error messages
    if (strstr(str, "expecting ;")) {
        str = "semicolon nazashti :\\";
    } else if (strstr(str, "syntax error, unexpected")) {
        str = "in chie neveshti? :\\ syntax ro check kon";
    }

    if (!error) 
        cerr << "Hoy! khate " << yylineno << " moshkel dare; "
             << str << endl;
}

void yyerror(const char *str, char chr) {
    // custom error message
    if (!strcmp(str, "bad token")) {
        str = " ro nemishnasam";
    }

    cerr << "Hoy! khatt'e " << yylineno << " eshtebahe! " 
         << "\"" << chr << "\"" << str << endl;

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
    Statements *stmtlist;
    Program *prog;
    /* ExpressionList *explist; */
}

%token<integer>    P_INT    "integer"
%token<float64>    P_FLOAT  "float64"
%token<ident>      P_IDENT  "ident"
%token             P_CHIZ   "chiz"
%token             P_PRINT  "print"
%token             P_INPUT  "input"
%token             P_IF     "agar"
%token             P_ELSE   "vagarna"
%token             P_WHILE  "ta"
%token             P_EQ     "=="
%token             P_NEQ    "!="
%token             P_LEQ    "<="
%token             P_GEQ    ">="
%token             P_L      "<"
%token             P_G      ">"
%token             P_MULEQ  "*="
%token             P_PLUSEQ "+="
%token             P_MINEQ  "-="
%token             P_DIVEQ   "/="
%token             P_MODEQ   "%="
%token             P_AND     "va"
%token             P_OR      "ya"
%token             P_EOL    ";"

%left P_AND P_OR
%left P_L P_LEQ P_G P_GEQ P_EQ P_NEQ
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS  "unary minus"

%type<exp> expression;
%type<stmt> statement;
%type<stmt> assignment;
%type<stmt> print;
%type<stmt> input;
%type<stmt> ifelse;
%type<stmt> whileloop;
%type<prog> program;
%type<stmtlist> statementlist;
/* %type<explist> expression_list; */


%%

main: /**/
    | program { delete $1; }
;

program: program statement { $1->exec($2); $$ = $1; }
       | statement { 
                        Program *prog = new Program; 
                        prog->exec($1);
                        $$ = prog;
                    }
;

statementlist: statementlist statement { $1->add($2); $$ = $1; }
             | statement { Statements *sl = new Statements; sl->add($1); $$ = sl; }

statement: assignment P_EOL
         | print      P_EOL
         | input      P_EOL
         | ifelse
         | whileloop 
;

assignment: P_CHIZ P_IDENT '=' expression {
            $$ = new DefAssign($2, $4);
            delete [] $2;
            }
          |
            P_CHIZ P_IDENT {
                $$ = new Define($2);
                delete [] $2;
            }
          |
            P_IDENT '=' expression {
            $$ = new Assign($1, $3);
            delete [] $1;
            }
          |
            P_IDENT P_PLUSEQ expression {
            $$ = new Assign($1, new Sum(new Identifier($1), $3));
            delete [] $1;
            }
          |
            P_IDENT P_MINEQ expression {
            $$ = new Assign($1, new Sub(new Identifier($1), $3));
            delete [] $1;
            }           
          |
            P_IDENT P_MULEQ expression {
            $$ = new Assign($1, new Mul(new Identifier($1), $3));
            delete [] $1;
            }
          |
            P_IDENT P_DIVEQ expression {
            $$ = new Assign($1, new Div(new Identifier($1), $3));
            delete [] $1;
            }
         |
            P_IDENT P_MODEQ expression {
            $$ = new Assign($1, new Mod(new Identifier($1), $3));
            delete [] $1;
            }
;

print: P_PRINT expression { $$ = new Print($2); }
;

input: P_INPUT P_IDENT { $$ = new Input($2); delete [] $2; }
;

ifelse: P_IF expression '{' statementlist '}'
        { $$ = new IfElse($2, $4); }
        |
        P_IF expression '{' statementlist '}' P_ELSE '{' statementlist '}'
        { $$ = new IfElse($2, $4, $8); }

whileloop: P_WHILE expression '{' statementlist '}'
         { $$ = new While($2, $4); }

expression: 
          '(' expression ')' { $$ = $2; }
          | P_INT   { $$ = new Constant($1); }
          | P_FLOAT { $$ = new Constant($1); }
          | P_IDENT {
                        $$ = new Identifier($1);
                        delete [] $1;
                    }
          | expression '+' expression   { $$ = new Sum($1, $3); }
          | expression '-' expression   { $$ = new Sub($1, $3); }
          | expression '*' expression   { $$ = new Mul($1, $3); }
          | expression '/' expression   { $$ = new Div($1, $3); }
          | expression '%' expression   { $$ = new Mod($1, $3); }
          | expression P_EQ expression  { $$ = new Equal($1, $3); }
          | expression P_NEQ expression { $$ = new NotEqual($1, $3); }
          | expression P_LEQ expression { $$ = new LessEqual($1, $3); }
          | expression P_GEQ expression { $$ = new GreaterEqual($1, $3); }
          | expression P_L expression   { $$ = new Less($1, $3); }
          | expression P_G expression   { $$ = new Greater($1, $3); }
          
          | expression P_AND expression   { $$ = new And($1, $3); }
          | expression P_OR  expression   { $$ = new Or($1, $3); }

          | '-' expression              { $$ = new Sub(new Constant(0), $2); }
          | '+' expression              { $$ = $2; }


; 

%%
