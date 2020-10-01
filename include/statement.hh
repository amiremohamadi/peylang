// compiler's internal statements
// TODO: switch to visitor design pattern in future

#ifndef STATEMENT_HH_
#define STATEMENT_HH_

#include <exception.hh>
#include <expression.hh>
#include <list>
#include <symtable.hh>

namespace pey {

class Statement {
public:
  virtual int eval(Symtable &smtbl) const = 0;
  virtual ~Statement() {}
};

class Statements {
private:
  std::list<Statement *> _statements;

public:
  ~Statements();
  void add(Statement *stmnt);
  int eval(Symtable &smtbl) const;
};

class Define : public Statement {
private:
  std::string _ident;

public:
  Define(const std::string &ident);
  int eval(Symtable &smtbl) const;
};

class Assign : public Statement {
private:
  std::string _ident;
  Expression *_expr;

public:
  Assign(const std::string &nm, Expression *expr);
  ~Assign();
  int eval(Symtable &smtbl) const;
};

class DefAssign : public Statement {
private:
  std::string _ident;
  Expression *_expr;

public:
  DefAssign(const std::string &ident, Expression *expr);
  ~DefAssign();
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

class Input : public Statement {
private:
  std::string _ident;

public:
  Input(std::string ident);
  int eval(Symtable &smtbl) const;
};

class IfElse : public Statement {
private:
  Expression *_condition;
  Statements *_true_list, *_false_list;

public:
  IfElse(Expression *condition, Statements *true_list);
  IfElse(Expression *condition, Statements *true_list, Statements *false_list);
  ~IfElse();
  int eval(Symtable &smtbl) const;
};

class While : public Statement {
private:
  Expression *_condition;
  Statements *_true_list;

public:
  While(Expression *condition, Statements *true_list);
  ~While();
  int eval(Symtable &smtbl) const;
};

} // namespace pey

#endif // STATEMENT_HH_
