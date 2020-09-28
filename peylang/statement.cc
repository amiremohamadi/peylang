#include <iostream>
#include <statement.hh>

namespace pey {
// assignment
Assign::Assign(const std::string &nm, Expression *expr)
    : _ident(nm), _expr(expr) {}

Assign::~Assign() { delete this->_expr; }

int Assign::eval(Symtable &smtbl) const {
  smtbl[this->_ident] = this->_expr->eval(smtbl);
  return 0;
}

// print statement
Print::Print(Expression *expr) : _expr(expr) {}

Print::~Print() { delete this->_expr; }

int Print::eval(Symtable &smtbl) const {
  // crete new object to print out
  Object obj(this->_expr->eval(smtbl));
  std::cout << obj << "\n";
  return 0;
}

// if else statement
IfElse::IfElse(Expression *condition, StatementList *true_list)
    : _condition(condition), _true_list(true_list),
      _false_list(new StatementList()) {}

IfElse::IfElse(Expression *condition, StatementList *true_list,
               StatementList *false_list)
    : _condition(condition), _true_list(true_list), _false_list(false_list) {}

IfElse::~IfElse() {
  delete _condition;
  delete _true_list;
  delete _false_list;
}

int IfElse::eval(Symtable &smtbl) const {
  // TODO: use a wrapoer class instead of list as statement list
  if (_condition->eval(smtbl) > 0) {
    for (auto exp : *_true_list) {
      exp->eval(smtbl);
    }
  } else {
    for (auto exp : *_false_list) {
      exp->eval(smtbl);
    }
  }

  // TODO: return value of exp->eval
  return 0;
}

} // namespace pey
