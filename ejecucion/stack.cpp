#include <iostream>
#include <string>
#include <list>

#include "stack.h"
#include "base.h"
#include "RInteger.h"

class RString;

std::unordered_map<std::string, RObject*> tsimbolos;
std::unordered_map<std::string, std::list<Instruccion*> *> functions;

std::unordered_map<std::string, RObject*> gobal_variables; // las variables deben agregarse a este hash variables["nombre"] = RObject*
std::unordered_map<std::string, std::list<Instruccion*>*> gobal_methods; // los metodos globales se guardan aqui methods["nombre"] = std::list<Instruccion *>*

void ejecutar(std::list<Instruccion*> *codigo) {
  std::list<Instruccion *>::iterator it = codigo->begin();
  Instruccion *ri;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : std::cout << "Fin ejecución" << std::endl; break;
      case PUTS  : puts((RString *)ri->arg1); break;
      case GETS  : gets((RString *)ri->arg1); break;
      case ADD   : ri->arg3 = add((RInteger *)ri->arg1, (RInteger *)ri->arg2); break;
      case OBJID : if (ri->arg1 != NULL) *((RInteger*)ri->arg1) = getDir(ri->arg2); break;
    }
  } while (ri->op != FIN);
}
