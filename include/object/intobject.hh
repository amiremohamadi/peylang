// integer object stuffs 

#ifndef INTOBJECT_HH_
#define INTOBJECT_HH_

#include <object/object.hh>

namespace pey {

class IntObject {
public:
  static Object add(const Object &left, const Object &right);
  static Object sub(const Object &left, const Object &right);
  static Object mul(const Object &left, const Object &right);
  static Object div(const Object &left, const Object &right);
  static Object mod(const Object &left, const Object &right);

  static bool equal(const Object &left, const Object &right);
  static bool not_equal(const Object &left, const Object &right);
  static bool less_equal(const Object &left, const Object &right);
  static bool greater_equal(const Object &left, const Object &right);
  static bool less(const Object &left, const Object &right);
  static bool greater(const Object &left, const Object &right);
};

} // namespace pey

#endif // INTOBJECT_HH_
