// TODO: visitor design pattern

#ifndef EXPRESSION_HH_
#define EXPRESSION_HH_

namespace pey {

class Expression {
public:
  virtual Object eval(Symtable &smtbl) const = 0;
};

class BinaryOperation : public Expression {
protected:
  Expression *_left, *_right;

public:
  explicit BinaryOperation(Expression *left, Expression *right)
      : _left(left), _right(right) {}

  ~BinaryOperation();
  virtual Object eval(Symtable &smtbl) const = 0;
};

class Sum : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Sub : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Mul : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Div : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

} // namespace pey
#endif // EXPRESSION_HH_
