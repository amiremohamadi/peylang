#ifndef SCANNER_HH_
#define SCANNER_HH_

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "location.hh"
#include "parser.tab.hh"

namespace pey {
class Scanner : public yyFlexLexer {
private:
  pey::Parser::semantic_type *yylval = nullptr;

public:
  Scanner(std::istream *input);

  // get rid of overriding virtual function warning
  using FlexLexer::yylex;
  virtual int yylex(pey::Parser::semantic_type *const lval,
                    pey::Parser::location_type *location);
};
} // namespace pey

#endif /* END SCANNER_HH_ */
