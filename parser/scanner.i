/* this file will generate the actual scanner for peylang */
%option noyywrap
%option yylineno
%option yyclass="pey::Scanner"
%option c++

%{
#include "tokens.hh"
#include "scanner.hh"
%}

t_identifier [_a-zA-Z][_0-9a-zA-Z]*
t_integer    [0-9]+
t_float      [0-9]+\.[0-9]+

%%
[ \t\n]   {/* ignore whitespaces */}
{t_integer} {  return T_INT; }
{t_float} {  return T_FLOAT; }
%%

