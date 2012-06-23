#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>
#include <unordered_map>

class RObject;

enum code_ops { FIN, PUTS, GETS, OBJID, ADD, ASSIGN_TMP, MULT, SUB, DIV, POW, MOD, IF, ELSIF, ELSIFCOND, WHILE, ELSE, END, AND, OR, DO };
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

void initializer();
//RObject *getValue(std::string* key);
void ejecutar(std::list<Instruccion*> *codigo);
Instruccion *nuevaInst(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3);
std::list<Instruccion*>::iterator descartar_hasta_end(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_if(std::list<Instruccion*>::iterator it);
void add_global_function(char* name, std::list<Instruccion*>* codigo);
void set_variable(char *name, RObject* var);
RObject *get_variable(char *name);
void add_symbol(char *name);
#endif
