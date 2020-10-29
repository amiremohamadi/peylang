#include <object/types.hh>

namespace pey {

std::string type_name(int type) {
  // helper funciotn to retrieve and get type_name as a string
  std::string result;
  switch (type) {
  case INT:
    result = "int";
    break;
  case FLOAT:
    result = "float";
    break;
  case STRING:
    result = "string";
    break;
  default:
    result = "unknown";
  }
  return result;
}

} // namespace pey
