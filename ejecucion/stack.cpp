#include "stack.h"
#include "base.h"
#include <iostream>
#include <string>
#include <list>

std::unordered_map<std::string, RObject*> tsimbolos;
std::unordered_map<std::string, std::list<Instruccion*> *> functions;

void ejecutar(std::list<Instruccion*> *codigo) {
  std::list<Instruccion *>::iterator it = codigo->begin();
  Instruccion *ri;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : std::cout << "Fin ejecución" << std::endl; break;
      case PUTS  : puts((RString *)ri->arg1->dir); break;
      case GETS  : gets((RString *)ri->arg1->dir); break;
      case OBJID : if (ri->arg1 != NULL) ((RInteger*)ri->arg1->dir)->value = getDir(ri->arg2->dir); break;
    }
  } while (ri->op != FIN);
}
