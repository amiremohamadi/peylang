#ifndef EXCEPTION_HH_
#define EXCEPTION_HH_

extern int yylineno;

class ParseException {
protected:
  int _line; // line number
  std::string _message;
  ParseException(std::string message) : _message(message), _line(yylineno) {}

public:
  virtual const char *what() const throw();
};

class UnboundIdent : public ParseException {
public:
  UnboundIdent() : ParseException("identifier tarif nashode") {}
};

#endif // EXCEPTION_HH_
