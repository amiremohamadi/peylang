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

Object Equal::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) == this->_right->eval(smtbl);
}

Object NotEqual::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) != this->_right->eval(smtbl);
}

Object LessEqual::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) <= this->_right->eval(smtbl);
}

Object GreaterEqual::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) >= this->_right->eval(smtbl);
}

Object Less::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) < this->_right->eval(smtbl);
}

Object Greater::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) > this->_right->eval(smtbl);
}

} // namespace pey
