#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

class RObject;
class RDecimal;
class RNumeric;
class RString;

enum code_ops { FIN, PUTS, GETS, CALL, OBJID, ADD, ASSIGN_TMP, MULT, SUB, DIV, POW, MOD, IF, ELSIF, ELSIFCOND, WHILEEND, WHILE, CASE, CASEREC, CASERECCOND, ELSE, END, AND, OR, NOT, G, GE, L, LE, EQ, NEQ, TOBOOL, DO, GETV, PUTV, ASGN, PUSH_ARG, ENDFUNC, RETURN, POP_ARG };
/*
 * G  - mayor
 * GE - mayor igual
 * L  - menor
 * LE - menor igual
 * EQ - igualdad
 * NEQ - !igualdad
 * TOBOOL - (value)
 * */
enum tipo_dir { CONSTANTE, TEMPORAL, VARIABLE, ETIQUETA };

struct RInstruccion {
  enum code_ops op;
  RObject *arg1, *arg2, *arg3;
  int linea;
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
std::list<Instruccion*>::iterator descartar_case_hasta_end(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_case(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_whileend(std::list<Instruccion*>::iterator it);
void add_global_function(char* name, std::list<Instruccion*>* codigo);
void set_variable(const char *name, RObject* var);
void set_variable(RString* str, RObject* var);
void set_global_variable(std::string *name, RObject* var);
RObject *get_variable(const char *name);
RObject* get_variable(RString* str);
void add_symbol(char *name);
void decimal_add(RDecimal* arg1, RNumeric* arg2, RNumeric* arg3);
bool operacion_es_booleana(enum code_ops op);
std::list<Instruccion*>::iterator get_function_iterator(RString* name);
void new_scope();
void drop_scope();
#endif
