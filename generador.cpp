#include <iostream>
#include <list>

#include "generador.h"
#include "ast.h"

using namespace std;

void generar(ast* arbol, std::list<Instruccion*> *codigo){
  if (arbol->tipo != t_compstmt)
    cout << "El arbol deberia ser compstmt" << endl;
  else
    generar_compstmt(arbol->stmt_list, codigo);
}

void generar_compstmt(list<ast*> *stmt_list, list<Instruccion*> *codigo){
  list<ast*>::iterator it;
  for (it=stmt_list->begin(); it != stmt_list->end(); it++){
    ast* nodo = *it;
    switch(nodo->tipo){
      case c_if :
        generar_if(nodo, codigo);
        break;
      case op_mul :
        generar_mul(nodo, codigo);
        break;
      case op_plus :
        generar_plus(nodo, codigo);
        break;
      case op_div :
        generar_div(nodo, codigo);
        break;
      case op_sub :
        generar_sub(nodo, codigo);
        break;
      case op_pow :
        generar_pow(nodo, codigo);
        break;
      case op_mod :
        generar_mod(nodo, codigo);
        break;
      case c_elsif :
        generar_elsif(nodo, codigo);
        break;
      case c_while :
        generar_while(nodo, codigo);
        break;
      case f_string :
        generar_string(nodo, codigo);
        break;
      case f_entero :
        generar_entero(nodo, codigo);
        break;
      case f_decimal :
        generar_decimal(nodo, codigo);
        break;
      case f_bool :
        generar_bool(nodo, codigo);
        break;
      case t_puts :
        generar_puts(nodo, codigo);
        break;
      case t_compstmt : // creo q nunca entra aca
        generar_compstmt(nodo->stmt_list, codigo);
        break;
    }
  }
}

void printTree(ast* tree){
  if (tree == NULL)
    return;
  switch(tree->tipo){
    case c_if :
      cout << "if stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      printTree(tree->h3);
      printTree(tree->h4);
      break;
    case op_mul :
      cout << "mul stmt" << endl;
      break;
    case op_plus :
      cout << "plus stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case op_div :
      cout << "div stmt" << endl;
      break;
    case op_sub :
      cout << "sub stmt" << endl;
      break;
    case op_pow :
      cout << "pow stmt" << endl;
      break;
    case op_mod :
      cout << "mod  stmt" << endl;
      break;
    case c_elsif :
      cout << "elsif stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      printTree(tree->h3);
      break;
    case c_while :
      cout << "while stmt" << endl;
      break;
    case f_string :
      cout << "string stmt: " << tree->str << endl;
      break;
    case f_entero :
      cout << "entero stmt" << tree->entero << endl;
      break;
    case f_decimal :
      cout << "decimal stmt" << endl;
      break;
    case f_bool :
      cout << "bool stmt: " << (tree->booleano ? "true" : "false") << endl;
      break;
    case t_puts :
      cout << "puts stmt" << endl;
      printTree(tree->h1);
      break;
    case t_gets :
      cout << "gets stmt" << endl;
      break;
    case t_method_call:
      cout << "method call " << tree->str << endl;
      break;
    case t_command :
      cout << "command stmt" << tree->str << endl;
      break;
    case t_nil :
      cout << "nil stmt" << endl;
      break;
    case t_mul_string :
      cout << "mul string stmt: " << tree->entero << endl;
      printTree(tree->h1);
      break;
    case t_add_string :
      cout << "add string stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case t_method_with_args:
      cout << "method call with args: " << tree->str << endl;
      printTree(tree->h1);
      break;
    case t_args:
      cout << "method call argument: " << endl;
      printList(tree->stmt_list);
      break;
    case b_and:
      cout << "and stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_or:
      cout << "or stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_not:
      cout << "not stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_mayor:
      cout << "mayor stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_mayor_igual:
      cout << "mayor igual stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_menor:
      cout << "menor stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_menor_igual:
      cout << "menor igual stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_doble_igual:
      cout << "doble igual stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_not_igual:
      cout << "not igual stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case b_is_bool:
      cout << "is bool stmt" << endl;
      printTree(tree->h1);
      printTree(tree->h2);
      break;
    case t_compstmt : // creo q nunca entra aca
      cout << "compstmt stmt" << endl;
      printList(tree->stmt_list);
      break;
    }
}

void printList(list<ast*> *stmt_list){ list<ast*>::iterator it;
  for (it=stmt_list->begin(); it != stmt_list->end(); it++)
    printTree(*it);
}

void generar_if(ast* nodo, std::list<Instruccion*> *codigo){}
RNumeric* generar_mul(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
RNumeric* generar_plus(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
RNumeric* generar_div(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
RNumeric* generar_sub(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
RNumeric* generar_pow(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
RInteger* generar_mod(ast* nodo, std::list<Instruccion*> *codigo){ return NULL; }
void generar_elsif(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_while(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_string(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_entero(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_decimal(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_bool(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_puts(ast* nodo, std::list<Instruccion*> *codigo){}


void freeList(list<ast*> *stmt_list){
  list<ast*>::iterator it;
  for (it=stmt_list->begin(); it != stmt_list->end(); it++)
    freeTree(*it);
  delete stmt_list;
}

void freeTree(ast* tree){
  if (tree == NULL)
    return;
  switch(tree->tipo){
    case c_if :
      break;
    case op_mul :
      break;
    case op_plus :
      freeTree(tree->h1);
      freeTree(tree->h2);
      delete tree;
      break;
    case op_div :
      freeTree(tree->h1);
      freeTree(tree->h2);
      delete tree;
      break;
    case op_sub :
      freeTree(tree->h1);
      freeTree(tree->h2);
      delete tree;
      break;
    case op_pow :
      freeTree(tree->h1);
      freeTree(tree->h2);
      delete tree;
      break;
    case op_mod :
      freeTree(tree->h1);
      freeTree(tree->h2);
      delete tree;
      break;
    case c_elsif :
      break;
    case c_while :
      break;
    case f_string :
      delete tree->str;
      delete tree;
      break;
    case f_entero :
      delete tree;
      break;
    case f_decimal :
      delete tree;
      break;
    case f_bool :
      delete tree;
      break;
    case t_puts :
      freeTree(tree->h1);
      delete tree;
      break;
    case t_gets :
      delete tree;
      break;
    case t_method_call:
      delete tree->str;
      delete tree;
      break;
    case t_command:
      delete tree->str;
      delete tree;
      break;
    case t_nil:
      delete tree;
      break;
    case t_mul_string :
      freeTree(tree->h1);
      break;
    case t_add_string :
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_and:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_or:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_not:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_mayor:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_mayor_igual:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_menor:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_menor_igual:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_doble_igual:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_not_igual:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case b_is_bool:
      freeTree(tree->h1);
      freeTree(tree->h2);
      break;
    case t_compstmt : // creo q nunca entra aca
      freeList(tree->stmt_list);
      delete tree;
      break;
    }
}
