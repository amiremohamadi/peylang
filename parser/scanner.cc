#include "scanner.hh"

tu::Scanner::Scanner(std::istream *input) : yyFlexLexer(input) {
  // Scanner class is not handling memory management and
  // you should be very careful about dangling pointer and memory leaking

  // unimplemented
}
