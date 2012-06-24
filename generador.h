#ifndef _GENERADOR_H
#define _GENERADOR_H

#include <iostream>
#include <list>

#include "ast.h"
#include "ejecucion/stack.h"

class RNumeric;
class RInteger;

void generar(ast* arbol, std::list<Instruccion*> *codigo);
void generar_compstmt(std::list<ast*> *stmt_list, std::list<Instruccion*> *codigo);
void generar_if(ast* nodo, std::list<Instruccion*> *codigo);
RNumeric* generar_mul(ast* nodo, std::list<Instruccion*> *codigo);
RNumeric* generar_plus(ast* nodo, std::list<Instruccion*> *codigo);
RNumeric* generar_div(ast* nodo, std::list<Instruccion*> *codigo);
RNumeric* generar_sub(ast* nodo, std::list<Instruccion*> *codigo);
RNumeric* generar_pow(ast* nodo, std::list<Instruccion*> *codigo);
RInteger* generar_mod(ast* nodo, std::list<Instruccion*> *codigo);
void generar_elsif(ast* nodo, std::list<Instruccion*> *codigo);
void generar_while(ast* nodo, std::list<Instruccion*> *codigo);
void generar_string(ast* nodo, std::list<Instruccion*> *codigo);
void generar_entero(ast* nodo, std::list<Instruccion*> *codigo);
void generar_decimal(ast* nodo, std::list<Instruccion*> *codigo);
void generar_bool(ast* nodo, std::list<Instruccion*> *codigo);
void generar_puts(ast* nodo, std::list<Instruccion*> *codigo);
void printList(std::list<ast*> *stmt_list);
void printTree(ast* tree);
void freeTree(ast* tree);
bool nodo_hoja(ast* nodo);
void generar_gets(std::list<Instruccion*>* codigo);
RNumeric* get_numeric_node(ast* hoja);
Instruccion* instr(enum code_ops op);
Instruccion* instr(enum code_ops op, RObject* arg1);
Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2);
Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3);

#endif
