#include <object/floatobject.hh>

namespace pey {

Object FloatObject::add(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._float + right._int);
  case FLOAT:
    return Object(left._float + right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "+");
  }
}

Object FloatObject::sub(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._float - right._int);
  case FLOAT:
    return Object(left._float - right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "-");
  }
}

Object FloatObject::mul(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._float * right._int);
  case FLOAT:
    return Object(left._float * right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "*");
  }
}

Object FloatObject::div(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return Object(left._float / right._int);
  case FLOAT:
    return Object(left._float / right._float);
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "/");
  }
}

bool FloatObject::equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return left._float == right._int;
  case FLOAT:
    return left._float == right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "==");
  }
}

bool FloatObject::not_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  return !FloatObject::equal(left, right);
}

bool FloatObject::less_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return left._float <= right._int;
  case FLOAT:
    return left._float <= right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "<=");
  }
}

bool FloatObject::greater_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return left._float >= right._int;
  case FLOAT:
    return left._float >= right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), ">=");
  }
}

bool FloatObject::less(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return left._float < right._int;
  case FLOAT:
    return left._float < right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "<");
  }
}

bool FloatObject::greater(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  switch (right._type) {
  case INT:
    return left._float > right._int;
  case FLOAT:
    return left._float > right._float;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), ">");
  }
}

} // namespace pey
