#include "stack.h"
#include "base.h"
#include <iostream>
#include <string>

void ejecutar(struct instruccion *codigo) {
  int ip=0;
  struct instruccion ri;
  do {
    ri = codigo[ip++];
    switch (ri.op) {
      case FIN : std::cout << "Fin ejecución" << std::endl; break;
      case PUTS : puts((RString *)ri.arg1); break;
      case GETS : gets((RString *)ri.arg1); break;
    }
  } while (ri.op != FIN);
}
