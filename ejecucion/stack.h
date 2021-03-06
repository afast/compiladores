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
class RClass;

enum code_ops { FIN, PUTS, GETS, CALL, ADD, ASSIGN_TMP, MULT, SUB, DIV, POW, MOD, IF, ELSIF, ELSIFCOND,
  WHILEEND, WHILE, CASE, CASEREC, CASERECCOND, ELSE, END, AND, OR, NOT, G, GE, L, LE, EQ, NEQ, TOBOOL, DO,
  GETV, PUTV, ASGN, GETV_ARR, PUSH_ARG, ENDFUNC, RETURN, POP_ARG, CLASS_INST_CALL, PUT_INST_V, GET_INST_V, NEW,
  WRITE_ATTR, SET_ARR_POS, PUTS_COMMAND, SIZE, NEW_SCOPE, DROP_SCOPE, TO_S, OBJECT_ID, INSTANCE_OF, RESPOND_TO
};
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

struct function_info_t {
  int param_count;
  RString* name;
  std::list<Instruccion*> *codigo;
};

typedef function_info_t function_info;

void initializer();
//RObject *getValue(std::string* key);
void ejecutar(std::list<Instruccion*> *codigo);
Instruccion *nuevaInst(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3);
std::list<Instruccion*>::iterator descartar_hasta_end(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_if(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_case_hasta_end(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_case(std::list<Instruccion*>::iterator it);
std::list<Instruccion*>::iterator descartar_whileend(std::list<Instruccion*>::iterator it);
void add_global_function(char* name, function_info* funcion);
void set_variable(const char *name, RObject* var);
void set_variable(RString* str, RObject* var);
void set_global_variable(std::string *name, RObject* var);
RObject *get_variable(const char *name);
RObject* get_variable(RString* str);
void decimal_add(RDecimal* arg1, RNumeric* arg2, RNumeric* arg3);
bool operacion_es_booleana(enum code_ops op);
std::list<Instruccion*>::iterator get_function_iterator(RString* name);
void new_scope();
void drop_scope();
void add_class(RClass* clase);
#endif
