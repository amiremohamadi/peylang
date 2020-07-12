#include <object.hh>

namespace pey {
Object::Object() : _val(0), _type(INT) {}

Object::Object(const int val) : _val(val), _type(INT) {}

Object::Object(const double val) : _val(val), _type(FLOAT) {}

std::ostream &operator<<(std::ostream &os, const Object &obj) {
  if (obj._type == INT)
    return os << obj._val._int;
  return os << obj._val._float;
}

Object Object::operator+(const Object &obj) const {
  if (_type == INT && obj._type == INT) {
    return Object(_val._int + obj._val._int);
  } else if (_type == INT && obj._type == FLOAT) {
    return Object(_val._int + obj._val._float);
  } else if (_type == FLOAT && obj._type == INT) {
    return Object(_val._float + obj._val._int);
  }
  return Object(_val._float + obj._val._float);
}

Object Object::operator-(const Object &obj) const { return Object(1); }

Object Object::operator*(const Object &obj) const { return Object(1); }

Object Object::operator/(const Object &obj) const { return Object(1); }
} // namespace pey
