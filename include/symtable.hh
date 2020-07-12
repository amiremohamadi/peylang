// compiler's internal symbol tables

#ifndef SYMTABLE_HH_
#define SYMTABLE_HH_

#include <map>
#include <object.hh>

namespace pey {

class Symtable {
private:
  // mapping identifiers (with type std::string) to objects
  // TODO: typedef identifier as std::string
  std::map<std::string, Object> _lookup;

public:
  Object &operator[](std::string ident);
};

} // namespace pey
#endif // SYMTABLE_HH_
