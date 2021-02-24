#include <object/stringobject.hh>

namespace pey {

std::string StringObject::stringify(std::string str) { return "'" + str + "'"; }

bool StringObject::equal(const Object &left, const Object &right) {
#ifdef DEBUG
  assert(left._type == STRING);
#endif

  switch (right._type) {
  case STRING:
    return left._string == right._string;
  default:
    throw InvalidOperand(type_name(left._type), type_name(right._type), "==");
  }
}

Object StringObject::add(const Object &left, const Object &right) {
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

Object StringObject::length(const Object &obj) {
#ifdef DEBUG
  assert(obj._type == STRING);
#endif

  return Object((int)obj._string.size());
}

Object StringObject::get_item(const Object &left, const Object &right) {
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
