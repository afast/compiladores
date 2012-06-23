#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>
#include <unordered_map>

class RObject;

enum code_ops { FIN, PUTS, GETS, OBJID, ADD, ASSIGN_TMP, MULT, SUB, DIV, POW, MOD, AND, IF, ELSIF, ELSIFCOND, ELSE, END };
enum tipo_dir { CONSTANTE, TEMPORAL, VARIABLE, ETIQUETA };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
};

typedef RInstruccion Instruccion;

struct s_node_tac {
  char dir[10];
  enum tipo_dir tipo;
  std::list<Instruccion*> *codigo;
};

typedef s_node_tac node_tac;

void inicializer();
//RObject *getValue(std::string* key);
void ejecutar(std::list<Instruccion*> *codigo);
#endif
