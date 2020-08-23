#ifndef PROGRAM_HH_
#define PROGRAM_HH_

#include <list>
#include <statement.hh>
#include <symtable.hh>

namespace pey {

class Program {
private:
  // statements as a doubly-linked list
  std::list<Statement *> *_statements;
  Symtable _symtable;

public:
  Program(std::list<Statement *> *stmnts);
  ~Program();
  int eval();
};

} // namespace pey

#endif // PROGRAM_HH_
