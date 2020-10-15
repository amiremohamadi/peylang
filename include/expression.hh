// TODO: visitor design pattern

#ifndef EXPRESSION_HH_
#define EXPRESSION_HH_

#include <list>
#include <map>
#include <object.hh>
#include <string>
#include <symtable.hh>

namespace pey {

class Expression {
public:
  virtual Object eval(Symtable &smtbl) const = 0;
  virtual ~Expression() {}
};

class Constant : public Expression {
private:
  Object _obj;

public:
  Constant(const Object &obj) : _obj(obj) {}
  virtual Object eval(Symtable &smtbl) const { return _obj; }
};

class Identifier : public Expression {
private:
  std::string _name;

public:
  Identifier(const std::string &name) : _name(name) {}
  virtual Object eval(Symtable &smtbl) const { return smtbl[_name]; }
};

class Len : public Expression {
private:
  Expression *_exp;

public:
  Len(Expression *exp) : _exp(exp) {}
  virtual Object eval(Symtable &smtbl) const;
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

class Mod : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Equal : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class NotEqual : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class LessEqual : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class GreaterEqual : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Less : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Greater : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class And : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

class Or : public BinaryOperation {
public:
  using BinaryOperation::BinaryOperation;
  virtual Object eval(Symtable &smtbl) const;
};

typedef std::list<Expression *> ExpressionList;

} // namespace pey
#endif // EXPRESSION_HH_
