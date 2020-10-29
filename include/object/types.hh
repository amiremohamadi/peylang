#ifndef TYPES_HH_
#define TYPES_HH_

#include <string>

namespace pey {

typedef enum Type {
  INT,
  FLOAT,
  STRING,
} Type;

std::string type_name(int type);

} // namespace pey

#endif // TYPES_HH_
