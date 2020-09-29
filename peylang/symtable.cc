#include <symtable.hh>

namespace pey {

Object &Symtable::operator[](std::string ident) {
  // TODO: throw exception in case of not finding the ident
  return this->_lookup[ident];
}

int Symtable::count(std::string ident) { return this->_lookup.count(ident); }

} // namespace pey
