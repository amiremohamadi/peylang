#include <iostream>
#include <statement.hh>

namespace pey {

Statements::~Statements() {
  for (auto stmnt : _statements)
    delete stmnt;
}

void Statements::add(Statement *stmnt) { _statements.push_back(stmnt); }

int Statements::eval(Symtable &smtbl) const {
  for (auto stmnt : _statements)
    stmnt->eval(smtbl);
  return 0;
}

// Define (to define a variable)
Define::Define(const std::string &ident) : _ident(ident) {}

int Define::eval(Symtable &smtbl) const {
  smtbl[this->_ident];
  return 0;
}

// assignment
Assign::Assign(const std::string &nm, Expression *expr)
    : _ident(nm), _expr(expr) {}

Assign::~Assign() { delete this->_expr; }

int Assign::eval(Symtable &smtbl) const {
  if (smtbl.count(this->_ident) == 0) {
    throw UnboundIdent(_ident);
  }

  Object &obj = smtbl[this->_ident];
  obj = this->_expr->eval(smtbl);

  /* smtbl[this->_ident] = this->_expr->eval(smtbl); */
  return 0;
}

// Define and Assign in one line
DefAssign::DefAssign(const std::string &ident, Expression *expr)
    : _ident(ident), _expr(expr) {}

DefAssign::~DefAssign() { delete this->_expr; }

int DefAssign::eval(Symtable &smtbl) const {
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
IfElse::IfElse(Expression *condition, Statements *true_list)
    : _condition(condition), _true_list(true_list),
      _false_list(new Statements()) {}

IfElse::IfElse(Expression *condition, Statements *true_list,
               Statements *false_list)
    : _condition(condition), _true_list(true_list), _false_list(false_list) {}

IfElse::~IfElse() {
  delete _condition;
  delete _true_list;
  delete _false_list;
}

int IfElse::eval(Symtable &smtbl) const {
  // TODO: use a wrapoer class instead of list as statement list
  if (_condition->eval(smtbl) > 0)
    _true_list->eval(smtbl);
  else
    _false_list->eval(smtbl);

  // TODO: return value of exp->eval
  return 0;
}

// while loop statement
While::While(Expression *condition, Statements *true_list)
    : _condition(condition), _true_list(true_list) {}

While::~While() {
  delete _condition;
  delete _true_list;
}

int While::eval(Symtable &smtbl) const {
  while (_condition->eval(smtbl) > 0)
    _true_list->eval(smtbl);
  return 0;
}

} // namespace pey
