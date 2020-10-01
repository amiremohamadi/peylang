#include <object.hh>

namespace pey {

Object::Object() : _val(0), _type(INT) {}

Object::Object(const int val) : _val(val), _type(INT) {}

Object::Object(const double val) : _val(val), _type(FLOAT) {}

bool Object::and_(const Object &obj) const {
  return (_type == INT ? _val._int : _val._float) &&
         (obj._type == INT ? obj._val._int : obj._val._float);
}

bool Object::or_(const Object &obj) const {
  return (_type == INT ? _val._int : _val._float) ||
         (obj._type == INT ? obj._val._int : obj._val._float);
}

std::ostream &operator<<(std::ostream &os, const Object &obj) {
  return os << (obj._type == INT ? obj._val._int : obj._val._float);
}

std::istream &operator>>(std::istream &is, Object &obj) {
  auto float_regex = std::regex("[0-9]*\\.[0-9]+");
  auto int_regex = std::regex("[0-9]+");

  std::string input;
  std::cin >> input;

  // type checking
  if (std::regex_match(input, float_regex)) {
    obj._val = Value(std::stod(input));
    obj._type = FLOAT;
  } else if (std::regex_match(input, int_regex)) {
    obj._val = Value(std::stoi(input));
    obj._type = INT;
  } else {
    // throw
    // exception
  }

  return is;
}

bool operator==(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) ==
         (robj._type == INT ? robj._val._int : robj._val._float);
}

bool operator!=(const Object &lobj, const Object &robj) {
  return !(lobj == robj);
}

bool operator<=(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) <=
         (robj._type == INT ? robj._val._int : robj._val._float);
}

bool operator>=(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) >=
         (robj._type == INT ? robj._val._int : robj._val._float);
}

bool operator<(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) <
         (robj._type == INT ? robj._val._int : robj._val._float);
}

bool operator>(const Object &lobj, const Object &robj) {
  return (lobj._type == INT ? lobj._val._int : lobj._val._float) >
         (robj._type == INT ? robj._val._int : robj._val._float);
}

Object Object::operator+(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._int + obj._val._float);
    case INT:
      return Object(_val._int + obj._val._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._float + obj._val._float);
    case INT:
      return Object(_val._float + obj._val._int);
    }
  }

  return Object(-666);
}

Object Object::operator-(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._int - obj._val._float);
    case INT:
      return Object(_val._int - obj._val._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._float - obj._val._float);
    case INT:
      return Object(_val._float - obj._val._int);
    }
  }

  return Object(-666);
}

Object Object::operator*(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._int * obj._val._float);
    case INT:
      return Object(_val._int * obj._val._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._float * obj._val._float);
    case INT:
      return Object(_val._float * obj._val._int);
    }
  }

  return Object(-666);
}

Object Object::operator/(const Object &obj) const {
  switch (_type) {
  case INT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._int / obj._val._float);
    case INT:
      // divide by zero exception
      if (obj._val._int == 0)
        throw DivByZero();
      return Object(_val._int / obj._val._int);
    }

  case FLOAT:
    switch (obj._type) {
    case FLOAT:
      return Object(_val._float / obj._val._float);
    case INT:
      return Object(_val._float / obj._val._int);
    }
  }

  return Object(-666);
}

Object Object::operator%(const Object &obj) const {
  // TODO: float numbers doesn't have mod operator
  if (_type == FLOAT || obj._type == FLOAT)
    throw ModOnFloat();

  if (obj._val._int == 0)
    throw ModByZero();

  return Object(_val._int % obj._val._int);
}

} // namespace pey
