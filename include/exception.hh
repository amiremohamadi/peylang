#ifndef EXCEPTION_HH_
#define EXCEPTION_HH_

#include <exception>
#include <string>

extern int yylineno;

class ParseException {
protected:
  int _line; // line number
  std::string _message;
  ParseException(std::string message) : _message(message), _line(yylineno) {}

public:
  ~ParseException() {}
  virtual std::string what() const throw() { return _message; }
  virtual int getline() const { return _line; }
};

class UnboundIdent : public ParseException {
public:
  UnboundIdent(std::string ident)
      : ParseException("moteghayyere \"" + ident + "\"" + " tarif nashode") {}
};

class DivByZero : public ParseException {
public:
  DivByZero() : ParseException("taghsim bar sefr akhe?") {}
};

class ModByZero : public ParseException {
public:
  ModByZero() : ParseException("baghimande bar sefr akhe?") {}
};

class ModOnFloat : public ParseException {
public:
  ModOnFloat() : ParseException("baghimandeye adad ashari akhe?") {}
};

#endif // EXCEPTION_HH_
