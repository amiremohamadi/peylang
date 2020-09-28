// compiler's internal statements
// TODO: switch to visitor design pattern in future

#ifndef STATEMENT_HH_
#define STATEMENT_HH_

#include <expression.hh>
#include <list>
#include <symtable.hh>

namespace pey {

class Statement {
public:
  virtual int eval(Symtable &smtbl) const = 0;
};

class Statements {
private:
  std::list<Statement *> _statements;

public:
  std::list<Statement *> get_statements();
  void add(Statement *s);
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

class Print : public Statement {
private:
  Expression *_expr;

public:
  Print(Expression *expr);
  ~Print();
  int eval(Symtable &smtbl) const;
};

typedef std::list<Statement *> StatementList;

class IfElse : public Statement {
private:
  Expression *_condition;
  StatementList *_true_list, *_false_list;

public:
  IfElse(Expression *condition, StatementList *true_list);
  IfElse(Expression *condition, StatementList *true_list,
         StatementList *false_list);
  ~IfElse();
  int eval(Symtable &smtbl) const;
};

} // namespace pey

#endif // STATEMENT_HH_
