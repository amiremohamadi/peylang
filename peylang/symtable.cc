#include <symtable.hh>

namespace pey {
Object &Symtable::operator[](std::string ident) {
  // TODO: throw exception in case of not finding the ident
  return this->_lookup[ident];
}
} // namespace pey
