#include <object/intobject.hh>

namespace pey {

Object IntObject::add(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._int + right._int);
  case FLOAT:
    return Object(left._int + right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "+");
  }
}

Object IntObject::sub(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._int - right._int);
  case FLOAT:
    return Object(left._int - right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "-");
  }
}

Object IntObject::mul(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._int * right._int);
  case FLOAT:
    return Object(left._int * right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "*");
  }
}

Object IntObject::div(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    // special case: can't devide integer to zero
    // (float is okay, so it must only check in case of having two integers)
    if (right._int == 0)
      throw DivByZero();
    return Object(left._int / right._int);
  case FLOAT:
    return Object(left._int / right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "/");
  }
}

Object IntObject::mod(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    // special case: can't calculate mod of integer to zero
    if (right._int == 0)
      throw ModByZero();
    return Object(left._int % right._int);
  case FLOAT:
    // can't use mod on floating numbers
    throw ModOnFloat();
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "%");
  }
}

bool IntObject::equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return left._int == right._int;
  case FLOAT:
    return left._int == right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "==");
  }
}

bool IntObject::not_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  return !IntObject::equal(left, right);
}

bool IntObject::less_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return left._int <= right._int;
  case FLOAT:
    return left._int <= right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "<=");
  }
}

bool IntObject::greater_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return left._int >= right._int;
  case FLOAT:
    return left._int >= right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), ">=");
  }
}

bool IntObject::less(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return left._int < right._int;
  case FLOAT:
    return left._int < right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "<");
  }
}

bool IntObject::greater(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  switch (right._type) {
  case INT:
    return left._int > right._int;
  case FLOAT:
    return left._int > right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), ">");
  }
}

} // namespace pey
