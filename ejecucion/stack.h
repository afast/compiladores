#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>

#include "base.h"

enum code_ops { FIN, PUTS, GETS, OBJID };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
};

typedef RInstruccion Instruccion;

std::unordered_map<std::string, RObject*> variables; // las variables deben agregarse a este hash variables["nombre"] = RObject*
std::unordered_map<std::string, std::list<Instruccion*>*> methods; // los metodos globales se guardan aqui methods["nombre"] = std::list<Instruccion *>*

void ejecutar(std::list<Instruccion*> *codigo);
#endif
