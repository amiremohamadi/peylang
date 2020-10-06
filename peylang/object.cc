#include <object.hh>

namespace pey {

std::string type_name(int type) {
  std::string result;
  switch (type) {
  case INT:
    result = "int";
    break;
  case FLOAT:
    result = "float";
    break;
  case STRING:
    result = "string";
    break;
  default:
    result = "unknown";
  }
  return result;
}

void Object::_copy(const Object &obj) {
  switch (obj._type) {
  case INT:
    _int = obj._int;
    break;
  case FLOAT:
    _float = obj._float;
    break;
  case STRING:
    new (&_string) std::string(obj._string);
    break;
  default:
    // TODO: raise type exception
    break;
  }
  _type = obj._type;
}

void Object::_destroy() {
  // handle string in this case
  if (_type == STRING) {
    using std::string; // necessary to compile with clang
    _string.~string();
  }
}

Object::~Object() { _destroy(); }

Object::Object() : _int(0), _type(INT) {}

Object::Object(const Object &obj) { _copy(obj); }

Object::Object(const int val) : _int(val), _type(INT) {}

Object::Object(const double val) : _float(val), _type(FLOAT) {}

Object::Object(const std::string val) : _type(STRING) {
  new (&_string) std::string(val);
  _string.erase(_string.begin());
  _string.erase(_string.end() - 1);
}

Object::Object(const char *val) : _type(STRING) {
  new (&_string) std::string(val);
  _string.erase(_string.begin());
  _string.erase(_string.end() - 1);
}

Object &Object::operator=(const Object &obj) {
  // nothing to do in case of self-assignment
  if (&obj != this) {
    _destroy(); // good bye old value
    _copy(obj); // hello new value
  }
  return *this;
}

bool Object::and_(const Object &obj) const {
  return (_type == INT ? _int : _float) &&
         (obj._type == INT ? obj._int : obj._float);
}

bool Object::or_(const Object &obj) const {
  return (_type == INT ? _int : _float) ||
         (obj._type == INT ? obj._int : obj._float);
}

std::ostream &operator<<(std::ostream &os, const Object &obj) {
  switch (obj._type) {
  case INT:
    os << obj._int;
    break;
  case FLOAT:
    os << obj._float;
    break;
  case STRING:
    os << obj._string;
    break;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Object &obj) {
  auto float_regex = std::regex("[0-9]*\\.[0-9]+");
  auto int_regex = std::regex("[0-9]+");

  std::string input;
  std::cin >> input;

  // type checking
  if (std::regex_match(input, float_regex)) {
    obj._float = std::stod(input);
    obj._type = FLOAT;
  } else if (std::regex_match(input, int_regex)) {
    obj._int = std::stoi(input);
    obj._type = INT;
  } else {
    // throw
    // exception
  }

  return is;
}

bool operator==(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::equal(lobj, robj);
  case FLOAT:
    return FloatType::equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "==");
}

bool operator!=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::not_equal(lobj, robj);
  case FLOAT:
    return FloatType::not_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "!=");
}

bool operator<=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::less_equal(lobj, robj);
  case FLOAT:
    return FloatType::less_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "<=");
}

bool operator>=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::greater_equal(lobj, robj);
  case FLOAT:
    return FloatType::greater_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), ">=");
}

bool operator<(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::less(lobj, robj);
  case FLOAT:
    return FloatType::less(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "<");
}

bool operator>(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntType::greater(lobj, robj);
  case FLOAT:
    return FloatType::greater(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), ">");
}

Object Object::operator+(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntType::add(*this, obj);
  case FLOAT:
    return FloatType::add(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "+");
}

Object Object::operator-(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntType::sub(*this, obj);
  case FLOAT:
    return FloatType::sub(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "-");
}

Object Object::operator*(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntType::mul(*this, obj);
  case FLOAT:
    return FloatType::mul(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "*");
}

Object Object::operator/(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntType::div(*this, obj);
  case FLOAT:
    return FloatType::div(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "/");
}

Object Object::operator%(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntType::mod(*this, obj);
  case FLOAT:
    // we can't use mod on floating numbers
    throw ModOnFloat();
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "%");
}

// Object Classes
Object IntType::add(const Object &left, const Object &right) {
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

Object IntType::sub(const Object &left, const Object &right) {
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

Object IntType::mul(const Object &left, const Object &right) {
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

Object IntType::div(const Object &left, const Object &right) {
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

Object IntType::mod(const Object &left, const Object &right) {
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

bool IntType::equal(const Object &left, const Object &right) {
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

bool IntType::not_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == INT);
#endif

  return !IntType::equal(left, right);
}

bool IntType::less_equal(const Object &left, const Object &right) {
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

bool IntType::greater_equal(const Object &left, const Object &right) {
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

bool IntType::less(const Object &left, const Object &right) {
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

bool IntType::greater(const Object &left, const Object &right) {
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

// float type

Object FloatType::add(const Object &left, const Object &right) {
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

Object FloatType::sub(const Object &left, const Object &right) {
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

Object FloatType::mul(const Object &left, const Object &right) {
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

Object FloatType::div(const Object &left, const Object &right) {
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

bool FloatType::equal(const Object &left, const Object &right) {
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

bool FloatType::not_equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == FLOAT);
#endif

  return !FloatType::equal(left, right);
}

bool FloatType::less_equal(const Object &left, const Object &right) {
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

bool FloatType::greater_equal(const Object &left, const Object &right) {
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

bool FloatType::less(const Object &left, const Object &right) {
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

bool FloatType::greater(const Object &left, const Object &right) {
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
