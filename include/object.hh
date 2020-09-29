// object type internals

#ifndef OBJECT_HH_
#define OBJECT_HH_

#include <exception>
#include <iostream>

namespace pey {

typedef enum Type {
  INT,
  FLOAT,
} Type;

typedef union Value {
  int _int;
  double _float;
  Value(int i) : _int(i) {}
  Value(double f) : _float(f) {}
} Value;

class Object {
  // all types of data represent as object
private:
  Type _type;
  Value _val;

public:
  Object();
  Object(const int val);
  Object(const double val);

  bool and_(const Object &obj) const;
  bool or_(const Object &obj) const;

  friend std::ostream &operator<<(std::ostream &os, const Object &obj);
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
