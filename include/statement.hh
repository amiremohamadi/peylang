// compiler's internal statements
// TODO: switch to visitor design pattern in future

#ifndef STATEMENT_HH_
#define STATEMENT_HH_

#include <symtable.hh>

namespace pey {

class Statement {
public:
  virtual int eval(Symtable &smtbl) const = 0;
};

class Assign : public Statement {
private:
  std::string _ident;
  Expression *_expr;

public:
  Assign(std::string nm, Expression *expr);
  ~Assign();
  int eval(Symtable &smtbl) const;
};

class Print : public Statement {
private:
  Expression *_expr;

public:
  Print(Expression *expr);
  ~Print();
  int eval(Symtable &smtbl) const;
};

} // namespace pey

#endif // STATEMENT_HH_
