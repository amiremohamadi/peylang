#include <object.hh>

namespace pey {

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
  return (lobj._type == INT ? lobj._int : lobj._float) ==
         (robj._type == INT ? robj._int : robj._float);
}

bool operator!=(const Object &lobj, const Object &robj) {
  return !(lobj == robj);
}

bool operator<=(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._int : lobj._float) <=
         (robj._type == INT ? robj._int : robj._float);
}

bool operator>=(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._int : lobj._float) >=
         (robj._type == INT ? robj._int : robj._float);
}

bool operator<(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._int : lobj._float) <
         (robj._type == INT ? robj._int : robj._float);
}

bool operator>(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._int : lobj._float) >
         (robj._type == INT ? robj._int : robj._float);
}

Object Object::operator+(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_int + obj._float);
    case INT:
      return Object(_int + obj._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_float + obj._float);
    case INT:
      return Object(_float + obj._int);
    }
  }
  // TODO: refactor returning value
  return Object(-666);
}

Object Object::operator-(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_int - obj._float);
    case INT:
      return Object(_int - obj._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_float - obj._float);
    case INT:
      return Object(_float - obj._int);
    }
  }

  return Object(-666);
}

Object Object::operator*(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_int * obj._float);
    case INT:
      return Object(_int * obj._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_float * obj._float);
    case INT:
      return Object(_float * obj._int);
    }
  }

  return Object(-666);
}

Object Object::operator/(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_int / obj._float);
    case INT:
      // divide by zero exception
      if (obj._int == 0)
        throw DivByZero();
      return Object(_int / obj._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_float / obj._float);
    case INT:
      return Object(_float / obj._int);
    }
  }

  return Object(-666);
}

Object Object::operator%(const Object &obj) const {
  // TODO: float numbers doesn't have mod operator
  if (_type == FLOAT || obj._type == FLOAT)
    throw ModOnFloat();

  if (obj._int == 0)
    throw ModByZero();

  return Object(_int % obj._int);
}

} // namespace pey
