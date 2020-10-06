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

class Object {
  // all types of data represent as object
  friend class IntType;
  friend class FloatType;

private:
  Type _type;
  union {
    int _int;
    double _float;
    std::string _string;
  };

  // special methods to be used in complicated data types
  void _copy(const Object &obj);
  void _destroy();

public:
  ~Object();
  Object();
  Object(const Object &obj);
  Object(const int val);
  Object(const double val);
  Object(const std::string val);
  Object(const char *val);

  // assignment
  Object &operator=(const Object &obj);

  bool and_(const Object &obj) const;
  bool or_(const Object &obj) const;

  friend std::ostream &operator<<(std::ostream &os, const Object &obj);
  friend std::istream &operator>>(std::istream &is, Object &obj);

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
};

// Type Classes
// each type must have a util class that contains type operators
class IntType {
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

} // namespace pey
#endif // OBJECT_HH_
