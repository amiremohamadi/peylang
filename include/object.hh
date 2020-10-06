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

typedef union Value {
  int _int;
  double _float;
  std::string _string;
  Value(int i) : _int(i) {}
  Value(double f) : _float(f) {}
} Value;

class Object {
  // all types of data represent as object
private:
  Type _type;
  union {
    int _int;
    double _float;
    std::string _string;
  };

  /* Value _val; */

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

} // namespace pey
#endif // OBJECT_HH_
