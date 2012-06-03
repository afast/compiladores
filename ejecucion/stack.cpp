#include "base.h"
#include <iostream>
#include <string>
/* OPERATIONS: Internal Representation */
enum code_ops { FIN, PUTS };

void ejecutar();

struct instruccion {
  enum code_ops op;
  void *arg1, *arg2, *arg3;
};

struct instruccion ri;


struct instruccion codigo[999];
int ip=0; // instruction pointer

int main()  {
  std::string *test = new std::string("hola\na todos\n\n");
  RString s1;
  s1.cadena = test;
  struct instruccion i0;
  struct instruccion i1;
  i0.op = PUTS;
  i1.op = FIN;
  i0.arg1 = &s1;
  codigo[0] = i0;
  codigo[1] = i1;
  ejecutar();
  return 0;
}

void ejecutar() {
  do {
    ri = codigo[ip++];
    switch (ri.op) {
      case FIN : std::cout << "Fin ejecución" << std::endl; break;
      case PUTS : puts((RString *)ri.arg1); break;
    }
  } while (ri.op != FIN);
}
