#include <program.hh>

namespace pey {
/* Program::Program(std::list<Statement *> *stmnts) : _statements(stmnts) {} */

/* Program::~Program() { */
/*   // destruct all the statements and free the memory */
/*   for (auto stmnt : *(this->_statements)) */
/*     delete stmnt; */
/* } */

/* int Program::eval() { */
/*   // TODO: throw readable exceptions */
/*   for (auto stmnt : *(this->_statements)) */
/*     stmnt->eval(this->_symtable); */

/*   return 0; */
/* } */

void Program::exec(Statement *stmnt) {
  // insert new statement and execute it
  stmnt->eval(this->_symtable);
}

} // namespace pey
