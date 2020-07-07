#ifndef SCANNER_HH_
#define SCANNER_HH_

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace pey {
class Scanner : public yyFlexLexer {
public:
  Scanner(std::istream *input);
  virtual int yylex();
};
} // namespace pey

#endif /* END SCANNER_HH_ */
