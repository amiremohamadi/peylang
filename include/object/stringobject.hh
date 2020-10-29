// string object stuffs

#ifndef STRINGOBJECT_HH_
#define STRINGOBJECT_HH_

#include <object/object.hh>

namespace pey {

class StringObject {
private:
  static std::string stringify(std::string str);

public:
  static Object add(const Object &left, const Object &right);
  static Object length(const Object &obj);
  static Object get_item(const Object &left, const Object &right);
};

} // namespace pey

#endif // STRINGOBJECT_HH_
