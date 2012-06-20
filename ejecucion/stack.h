#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>
#include <unordered_map>

class RObject;

enum code_ops { FIN, PUTS, GETS, OBJID, ADD };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
};

typedef RInstruccion Instruccion;

struct s_node_tac {
  char var_tmp[10];
  std::list<Instruccion*> *usos;
};

typedef s_node_tac node_tac;

void ejecutar(std::list<Instruccion*> *codigo);
#endif
