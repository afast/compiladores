#include "base.h"
#include <iostream>
#include <list>
enum code_ops { FIN, PUTS, GETS, OBJID };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
};

typedef RInstruccion Instruccion;

void ejecutar(std::list<Instruccion*> *codigo);
