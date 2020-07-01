#ifndef SCANNER_HH_
#define SCANNER_HH_

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace tu {
class Scanner : public yyFlexLexer {
public:
  Scanner(std::istream *input);
  virtual int yylex();
};
} // namespace tu

#endif /* END SCANNER_HH_ */
