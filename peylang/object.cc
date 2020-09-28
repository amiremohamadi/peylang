#include <object.hh>

namespace pey {

Object::Object() : _val(0), _type(INT) {}

Object::Object(const int val) : _val(val), _type(INT) {}

Object::Object(const double val) : _val(val), _type(FLOAT) {}

std::ostream &operator<<(std::ostream &os, const Object &obj) {
  return os << (obj._type == INT ? obj._val._int : obj._val._float);
}

bool operator==(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) ==
         (robj._type == INT ? robj._val._int : robj._val._float);
}

Object Object::operator+(const Object &obj) const {
  return Object((_type == INT ? _val._int : _val._float) +
                (obj._type == INT ? obj._val._int : obj._val._float));
}

Object Object::operator-(const Object &obj) const {
  return Object((_type == INT ? _val._int : _val._float) -
                (obj._type == INT ? obj._val._int : obj._val._float));
}

Object Object::operator*(const Object &obj) const {
  return Object((_type == INT ? _val._int : _val._float) *
                (obj._type == INT ? obj._val._int : obj._val._float));
}

Object Object::operator/(const Object &obj) const {
  return Object((_type == INT ? _val._int : _val._float) /
                (obj._type == INT ? obj._val._int : obj._val._float));
}

} // namespace pey
