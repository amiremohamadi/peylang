// object type internals

#ifndef OBJECT_HH_
#define OBJECT_HH_

#include <exception.hh>
#include <exception>
#include <iostream>
#include <regex>
#include <string>

namespace pey {

typedef enum Type {
  INT,
  FLOAT,
  STRING,
} Type;

// util to get type name
std::string type_name(int type);

// Object class represent anytype objects
// containing int, float, string ...
// it uses many helper classes (type classes) to do stuff
// on each object type
class Object {
  // all types of data represent as object
  friend class IntType;
  friend class FloatType;
  friend class StringType;

private:
  Type _type;
  // representing value as a union, so
  // not that you're compiling the code with c++11 or higher
  // because of using unrestricted unions (std::string only supported in
  // unrestricted unions)
  union {
    int _int;
    double _float;
    std::string _string;
  };

  // in case of using complicated data-types like string, we need these
  // helper methods to have correct functionality and avoid memory leak
  void _copy(const Object &obj);
  void _destroy();

public:
  // free resources on destroy to avoid memory leak
  ~Object() { _destroy(); }
  // Object represents any data-type, so we have a constructor for each
  Object() : _int(0), _type(INT) {}
  Object(const Object &obj) { _copy(obj); }

  Object(const int val) : _int(val), _type(INT) {}
  Object(const double val) : _float(val), _type(FLOAT) {}

  Object(const char *val) : _type(STRING) {
    new (&_string) std::string(val);
    // remove quotes from sides of string
    _string.erase(_string.begin());
    _string.erase(_string.end() - 1);
  }

  Object(const std::string val) : Object(val.c_str()) {}

  // assignment, is needed in symbol table
  Object &operator=(const Object &obj);

  friend std::ostream &operator<<(std::ostream &os, const Object &obj);
  friend std::istream &operator>>(std::istream &is, Object &obj);

  bool logic_and(const Object &obj) const;
  bool logic_or(const Object &obj) const;

  friend bool operator==(const Object &lobj, const Object &robj);
  friend bool operator!=(const Object &lobj, const Object &robj);
  friend bool operator<=(const Object &lobj, const Object &robj);
  friend bool operator>=(const Object &lobj, const Object &robj);
  friend bool operator<(const Object &lobj, const Object &robj);
  friend bool operator>(const Object &lobj, const Object &robj);

  Object operator+(const Object &obj) const;
  Object operator-(const Object &obj) const;
  Object operator*(const Object &obj) const;
  Object operator/(const Object &obj) const;
  Object operator%(const Object &obj) const;

  Object length() const;
};

// Type Classes
// each type must have a util class that contains type operators
class IntType {
  // utils for integer value
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

class FloatType {
  // utils for float value
public:
  static Object add(const Object &left, const Object &right);
  static Object sub(const Object &left, const Object &right);
  static Object mul(const Object &left, const Object &right);
  static Object div(const Object &left, const Object &right);

  static bool equal(const Object &left, const Object &right);
  static bool not_equal(const Object &left, const Object &right);
  static bool less_equal(const Object &left, const Object &right);
  static bool greater_equal(const Object &left, const Object &right);
  static bool less(const Object &left, const Object &right);
  static bool greater(const Object &left, const Object &right);
};

class StringType {
  // utils fr string value
private:
  static std::string stringify(std::string str);

public:
  static Object add(const Object &left, const Object &right);
  static Object length(const Object &obj);
};

} // namespace pey
#endif // OBJECT_HH_
