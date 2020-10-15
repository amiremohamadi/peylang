#include <object.hh>

namespace pey {

std::string type_name(int type) {
  // helper funciotn to retrieve and get type_name as a string
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

// Object declarations

// copy method is needed by copy constructor and assignment
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

// TODO: is it need to destroy string?
void Object::_destroy() {
  // handle string in this case
  if (_type == STRING) {
    using std::string; // necessary to compile with clang
    _string.~string();
  }
}

Object &Object::operator=(const Object &obj) {
  // nothing to do in case of self-assignment
  if (&obj != this) {
    _destroy(); // good bye old value
    _copy(obj); // hello new value
  }
  return *this;
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
  }

  return is;
}

bool Object::logic_and(const Object &obj) const {
  return (_type == INT ? _int : _float) &&
         (obj._type == INT ? obj._int : obj._float);
}

bool Object::logic_or(const Object &obj) const {
  return (_type == INT ? _int : _float) ||
         (obj._type == INT ? obj._int : obj._float);
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
  case STRING:
    return StringType::add(*this, obj);
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

Object Object::length() const {
  switch (_type) {
  case STRING:
    return StringType::length(*this);
  }
  throw NotIterable(type_name(_type));
}

Object Object::get_item(const Object &obj) const {
  switch (_type) {
  case STRING:
    return StringType::get_item(*this, obj);
  }
  throw NotIterable(type_name(_type));
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

// string

std::string StringType::stringify(std::string str) { return "'" + str + "'"; }

Object StringType::add(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == STRING);
#endif

  switch (right._type) {
  case STRING:
    return Object(stringify(left._string + right._string));
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "+");
  }
}

Object StringType::length(const Object &obj) {
#ifdef DEBUG
  assert(obj._type == STRING);
#endif

  return Object((int)obj._string.size());
}

Object StringType::get_item(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == STRING);
#endif

  // only int as index
  if (right._type != INT)
    throw InvalidOperand(type_name(left._type), type_name(right._type), "[]");

  // check index bound
  if (right._int >= left._string.size() || right._int < 0)
    throw OutOfBoundIndex();

  // get item and because we're on c++ it returns char
  // so next step is to convert char to string (because in peylang we don't
  // have char, we only want strings)
  char chr = left._string[right._int];
  std::string item(1, chr);
  return Object(stringify(item));
}

} // namespace pey
