#include <expression.hh>

namespace pey {

Object Len::eval(Symtable &smtbl) const {
  return this->_exp->eval(smtbl).length();
}

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

Object Mod::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl) % this->_right->eval(smtbl);
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

Object And::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl).logic_and(this->_right->eval(smtbl));
}

Object Or::eval(Symtable &smtbl) const {
  return this->_left->eval(smtbl).logic_or(this->_right->eval(smtbl));
}

} // namespace pey
