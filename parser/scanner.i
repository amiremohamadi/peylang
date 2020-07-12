/* this file will generate the actual scanner for peylang */
%{
#include "scanner.hh"

#undef YY_DECL
#define YY_DECL int pey::Scanner::yylex(pey::Parser::semantic_type *const lval, pey::Parser::location_type *loc )
using token = pey::Parser::token;

%}

%option debug
%option yyclass="pey::Scanner"
%option noyywrap
%option c++


t_identifier [_a-zA-Z][_0-9a-zA-Z]*
t_integer    [0-9]+
t_float      [0-9]+\.[0-9]+

%%
[ \t\n]   {/* ignore whitespaces */}
{t_integer} {  return token::T_INT; }
{t_float} {  return token::T_FLOAT; }
%%

