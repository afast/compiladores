#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>
#include <unordered_map>

class RObject;

enum code_ops { FIN, PUTS, GETS, OBJID };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
};

typedef RInstruccion Instruccion;

void ejecutar(std::list<Instruccion*> *codigo);
#endif
