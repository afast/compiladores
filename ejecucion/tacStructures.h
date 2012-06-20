#ifndef _TACSTRUCTURES_H
#define _TACSTRUCTURES_H

#include <iostream>
#include <list>
#include <unordered_map>
#include "stack.h"

class RObject;


struct s_node_tac {
  char var_tmp[10];
  std::list<Instruccion*> *usos;
};

typedef s_node_tac node_tac;

#endif
