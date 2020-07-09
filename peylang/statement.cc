#include <iostream>
#include <statement.hh>

namespace pey {
// assignment
Assign::Assign(std::string nm, Expression *expr) : _ident(nm), _expr(expr) {}

Assing::~Assign() { delete this->_expr; }

int Assign::eval(Symtable &smtbl) const {
  smtbl[this->_ident] = this->_expr->eval(smtbl);
  return 0;
}

// print statement
Print::Print(Expression *expr) : _expr(expr) {}

Print::~Print() { delete this->_expr; }

int Print::eval(Symtabl &smtbl) const {
  // crete new object to print out
  Object obj(this->_expr->eval(smtbl));
  std::cout << obj << "\n";
  return 0;
}
} // namespace pey
