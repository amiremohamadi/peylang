#include <object/object.hh>
#include <object/stringobject.hh>
#include <object/intobject.hh>
#include <object/floatobject.hh>

namespace pey {

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
    return IntObject::equal(lobj, robj);
  case FLOAT:
    return FloatObject::equal(lobj, robj);
  case STRING:
    return StringObject::equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "==");
}

bool operator!=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntObject::not_equal(lobj, robj);
  case FLOAT:
    return FloatObject::not_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "!=");
}

bool operator<=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntObject::less_equal(lobj, robj);
  case FLOAT:
    return FloatObject::less_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "<=");
}

bool operator>=(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntObject::greater_equal(lobj, robj);
  case FLOAT:
    return FloatObject::greater_equal(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), ">=");
}

bool operator<(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntObject::less(lobj, robj);
  case FLOAT:
    return FloatObject::less(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), "<");
}

bool operator>(const Object &lobj, const Object &robj) {
  switch (lobj._type) {
  case INT:
    return IntObject::greater(lobj, robj);
  case FLOAT:
    return FloatObject::greater(lobj, robj);
  }
  throw InvalidOperand(type_name(lobj._type), type_name(robj._type), ">");
}

Object Object::operator+(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntObject::add(*this, obj);
  case FLOAT:
    return FloatObject::add(*this, obj);
  case STRING:
    return StringObject::add(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "+");
}

Object Object::operator-(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntObject::sub(*this, obj);
  case FLOAT:
    return FloatObject::sub(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "-");
}

Object Object::operator*(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntObject::mul(*this, obj);
  case FLOAT:
    return FloatObject::mul(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "*");
}

Object Object::operator/(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntObject::div(*this, obj);
  case FLOAT:
    return FloatObject::div(*this, obj);
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "/");
}

Object Object::operator%(const Object &obj) const {
  switch (_type) {
  case INT:
    return IntObject::mod(*this, obj);
  case FLOAT:
    // we can't use mod on floating numbers
    throw ModOnFloat();
  }
  throw InvalidOperand(type_name(_type), type_name(obj._type), "%");
}

Object Object::length() const {
  switch (_type) {
  case STRING:
    return StringObject::length(*this);
  }
  throw NotIterable(type_name(_type));
}

Object Object::get_item(const Object &obj) const {
  switch (_type) {
  case STRING:
    return StringObject::get_item(*this, obj);
  }
  throw NotIterable(type_name(_type));
}

} // namespace pey
