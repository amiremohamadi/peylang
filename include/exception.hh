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

class InvalidOperand : public ParseException {
public:
  InvalidOperand(std::string typel, std::string typer, std::string op)
      : ParseException("operatore " + op + " rooye " + typel + ", " + typer +
                       " tarif nashode.") {}
};

class NotIterable : public ParseException {
public:
  NotIterable(std::string typel) : ParseException(typel + ", iterable nist.") {}
};

#endif // EXCEPTION_HH_
