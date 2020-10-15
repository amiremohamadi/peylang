%option noyywrap
%option yylineno

%{

#include <string>
#include <sstream>
#include <expression.hh>
#include <statement.hh>
#include <program.hh>
#include "parser.tab.h"

using std::string;
using std::istringstream;

extern void yyerror(const char*, char);

%}

ident     [_a-zA-Z][_0-9a-zA-Z]*
integer   [0-9]+
float64   [0-9]*\.[0-9]+
str       '(\\.|[^\\'])*'

%%

[ \t\n]         { /*whitespaces*/ }
"--"[^\r\n]*    { /*comments*/ }
";"             { return P_EOL; }

"="             { return yytext[0]; }
"+"             { return yytext[0]; }
"-"             { return yytext[0]; }
"*"             { return yytext[0]; }
"/"             { return yytext[0]; }
"%"             { return yytext[0]; }

"{"             { return yytext[0]; }
"}"             { return yytext[0]; }
"("             { return yytext[0]; }
")"             { return yytext[0]; }

"=="            { return P_EQ;      }
"!="            { return P_NEQ;     }
"<="            { return P_LEQ;     }
">="            { return P_GEQ;     }
"<"             { return P_L;       }
">"             { return P_G;       }

"-="            { return P_MINEQ;   }
"+="            { return P_PLUSEQ;  }
"*="            { return P_MULEQ;   }
"/="            { return P_DIVEQ;   }
"%="            { return P_MODEQ;   }

"agar"          { return P_IF;      }
"vagarna"       { return P_ELSE;    }
"ta"            { return P_WHILE;   }
"chiz"          { return P_CHIZ;    }
"chaap"         { return P_PRINT;   }
"begir"         { return P_INPUT;   }
"andaze"        { return P_LEN;     }

"va"            { return P_AND;     }
"ya"            { return P_OR;      }

{ident}   {
            yylval.ident = new char[strlen(yytext) + 1];
            strcpy(yylval.ident, yytext);
            return P_IDENT;
          }

{integer} {
            istringstream(string(yytext)) >> yylval.integer;
            return P_INT;
          }

{float64} {
            istringstream(string(yytext)) >> yylval.float64;
            return P_FLOAT;
          }

{str}    {
            yylval.str = new char[strlen(yytext) + 1];
            strcpy(yylval.str, yytext);
            return P_STR;
          }

.         {
            yyerror("bad token", yytext[0]);
            yyterminate();
          }

%%
