#include <expression.hh>

namespace pey {
BinaryOperation::~BinaryOperation() {
  delete this->_left;
  delete this->_right;
}

Object Sum::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) + this->_right->eval(smtbl);
}

Object Sub::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) - this->_right->eval(smtbl);
}

Object Mul::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) * this->_right->eval(smtbl);
}

Object Div::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) / this->_right->eval(smtbl);
}
} // namespace pey
