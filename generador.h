#ifndef _GENERADOR_H
#define _GENERADOR_H

#include <iostream>
#include <list>

#include "ast.h"
#include "ejecucion/stack.h"

class RNumeric;
class RInteger;
class RVariable;
class RClass;

void generar(ast* arbol, std::list<Instruccion*> *codigo);
void generar_compstmt(std::list<ast*> *stmt_list, std::list<Instruccion*> *codigo);
void generar_if(ast* nodo, std::list<Instruccion*> *codigo);
void generar_pow(ast* nodo, std::list<Instruccion*> *codigo);
void generar_mod(ast* nodo, std::list<Instruccion*> *codigo);
void generar_elsif(ast* nodo, std::list<Instruccion*> *codigo);
void generar_while(ast* nodo, std::list<Instruccion*> *codigo);
void generar_case(ast* nodo, std::list<Instruccion*> *codigo);
void generar_case_rec(ast* nodo, std::list<Instruccion*> *codigo, RVariable* var);
void generar_string(ast* nodo, std::list<Instruccion*> *codigo);
void generar_entero(ast* nodo, std::list<Instruccion*> *codigo);
void generar_decimal(ast* nodo, std::list<Instruccion*> *codigo);
void generar_bool(ast* nodo, std::list<Instruccion*> *codigo);
void generar_puts(ast* nodo, std::list<Instruccion*> *codigo);
void generar_op_numerica(enum code_ops op, ast* nodo, std::list<Instruccion*>* codigo);
void generar_op_asgn(ast* nodo, std::list<Instruccion*>* codigo);
void printList(std::list<ast*> *stmt_list);
void printTree(ast* tree);
void freeTree(ast* tree);
bool nodo_hoja(ast* nodo);
void generar_gets(std::list<Instruccion*>* codigo, int linea);
RObject* get_numeric_node(ast* hoja);
Instruccion* instr(enum code_ops op, int linea);
Instruccion* instr(enum code_ops op, RObject* arg1, int linea);
Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2, int linea);
Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3, int linea);
void generar_op_booleana(enum code_ops op, ast* nodo, std::list<Instruccion*>* codigo);
RObject* get_abstract_node(ast* hoja);
void generar_suma_string(ast* nodo, std::list<Instruccion*>* codigo);
void generar_mul_string(ast* nodo, std::list<Instruccion*>* codigo);
function_info* generar_metodo(ast* nodo);
void generar_method_call(ast* nodo, std::list<Instruccion*>* codigo);
void push_args(ast* n, std::list<Instruccion*>* codigo, int linea);
void pop_args(ast* args, std::list<Instruccion*>* codigo);
void generar_arr_pos(ast* nodo, std::list<Instruccion*> *codigo);
RClass* generar_clase(ast* nodo, std::list<Instruccion*> *codigo);
void generar_instance_method_call(ast* nodo, std::list<Instruccion*> *codigo);
void generar_new(ast* nodo, std::list<Instruccion*> *codigo);
void generar_attr_writer(ast* nodo, std::list<Instruccion*> *codigo);
void generar_writers(ast* nodo);
void generar_accesores(ast* nodo);
void generar_readers(ast* nodo);
#endif
