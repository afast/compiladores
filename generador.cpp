#include <iostream>
#include <list>

#include "generador.h"
#include "ast.h"
#include "ejecucion/memory.h"
#include "ejecucion/RString.h"
#include "ejecucion/RDecimal.h"
#include "ejecucion/RInteger.h"
#include "ejecucion/RNumeric.h"
#include "ejecucion/RBool.h"
#include "ejecucion/stack.h"
#include "ejecucion/base.h"

using namespace std;

void generar(ast* arbol, std::list<Instruccion*> *codigo){
  if (arbol->tipo != t_compstmt)
    cout << "Error detectando programa, arbol deberia ser compstmt!" << endl;
  else
    generar_compstmt(arbol->stmt_list, codigo);
}

RObject* generar_objeto(ast* nodo){
  RObject* objeto;
  switch(nodo->tipo){
    case f_string :{
      RString* s = new RString(nodo->str);
      objeto = s;
      break;}
    case f_entero :{
      RInteger* s = new RInteger(nodo->entero);
      objeto = s;
      break;}
    case f_decimal :{
      cout << "detectado decimal: " << nodo->decimal << endl;
      RDecimal* s = new RDecimal(nodo->decimal);
      objeto = s;
      break;}
    case f_bool :{
      RBool* s = new RBool(nodo->booleano);
      objeto = s;
      break;}
  }
  return objeto;
}

void decidir_nodo(ast* nodo, list<Instruccion*> *codigo){
  if (nodo == NULL)
    return;
  switch(nodo->tipo){
    case c_if :
      cout << "generar if" << endl;
      generar_if(nodo, codigo);
      break;
    case op_mul :
      generar_op_numerica(MULT, nodo, codigo);
      break;
    case op_plus :
      generar_op_numerica(ADD, nodo, codigo);
      break;
    case op_div :
      generar_op_numerica(DIV, nodo, codigo);
      break;
    case op_sub :
      generar_op_numerica(SUB, nodo, codigo);
      break;
    case op_pow :
      generar_op_numerica(POW, nodo, codigo);
      break;
    case op_mod :
      generar_op_numerica(MOD, nodo, codigo);
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
    case t_gets : //Leer de la entrada estandar
      generar_gets(codigo);
      break;
    case t_method_call:
      cout << "method call " << nodo->str << endl;
      break;
    case t_command :
      cout << "command stmt" << nodo->str << endl;
      break;
    case t_nil :
      cout << "nil stmt" << endl;
      break;
    case t_mul_string :
      cout << "mul string stmt: " << nodo->entero << endl;
      break;
    case t_add_string :
      cout << "add string stmt" << endl;
      break;
    case t_method_with_args:
      cout << "method call with args: " << nodo->str << endl;
      break;
    case t_args:
      cout << "method call argument: " << endl;
      break;
    case b_and:
      generar_op_booleana(AND, nodo, codigo);
      cout << "and stmt" << endl;
      break;
    case b_or:
      generar_op_booleana(OR, nodo, codigo);
      cout << "or stmt" << endl;
      break;
    case b_not:
      generar_op_booleana(NOT, nodo, codigo);
      cout << "not stmt" << endl;
      break;
    case b_mayor:
      generar_op_booleana(G, nodo, codigo);
      cout << "mayor stmt" << endl;
      break;
    case b_mayor_igual:
      generar_op_booleana(GE, nodo, codigo);
      cout << "mayor igual stmt" << endl;
      break;
    case b_menor:
      generar_op_booleana(L, nodo, codigo);
      cout << "menor stmt" << endl;
      break;
    case b_menor_igual:
      generar_op_booleana(LE, nodo, codigo);
      cout << "menor igual stmt" << endl;
      break;
    case b_doble_igual:
      generar_op_booleana(EQ, nodo, codigo);
      cout << "doble igual stmt" << endl;
      break;
    case b_not_igual:
      generar_op_booleana(NEQ, nodo, codigo);
      cout << "not igual stmt" << endl;
      break;
    case b_is_bool:
      generar_op_booleana(TOBOOL, nodo, codigo);
      cout << "is bool stmt" << endl;
      break;
    case t_compstmt : // creo q nunca entra aca
      generar_compstmt(nodo->stmt_list, codigo);
      break;
    }
}

void generar_compstmt(list<ast*> *stmt_list, list<Instruccion*> *codigo){
  list<ast*>::iterator it;
  for (it=stmt_list->begin(); it != stmt_list->end(); it++){
    decidir_nodo(*it, codigo);
  }
  cout << "fin stmt_list" << endl;
}



void generar_if(ast* nodo, std::list<Instruccion*> *codigo){
  /*
   * h1 - condition
   * h2 - if_block
   * h3 - rec_elsif - optional
   * h4 - else      - optional
   * */
  /* evaluar condicion */
  /* if cond */
  /* cuerpo if */
  /* generar elsif */
  /* generar else */
  /* endif */
  decidir_nodo(nodo->h1, codigo);
  RObject* cond = codigo->back()->arg1;
  codigo->push_back(instr(IF, cond));
  generar_compstmt(nodo->h2->stmt_list, codigo);
  generar_elsif(nodo->h3, codigo);
  if (nodo->h4 != NULL){
    codigo->push_back(instr(ELSE));
    generar_compstmt(nodo->h4->stmt_list, codigo);
  }
  codigo->push_back(instr(END));
}

void generar_op_numerica(enum code_ops op, ast* nodo, std::list<Instruccion*>* codigo){
  RNumeric* arg2, *arg3, *arg1;
  if (nodo_hoja(nodo->h1)){ // no preciso variable temporal
    arg2 = get_numeric_node(nodo->h1);
  } else {
    decidir_nodo(nodo->h1, codigo); //ultima operacion debe ser numerica y guardar el resultado en arg1
    arg2 = (RNumeric*)codigo->back()->arg1;
  }
  if (nodo_hoja(nodo->h2)){ // no preciso variable temporal
    arg3 = get_numeric_node(nodo->h2);
  } else {
    decidir_nodo(nodo->h2, codigo); //ultima operacion debe ser numerica y guardar el resultado en arg1
    arg3 = (RNumeric*)codigo->back()->arg1;
  }

  if (arg2->es_dec() || arg3->es_dec()){
    RDecimal *d = new RDecimal();
    arg1 = d;
  }else{
    RInteger *i = new RInteger();
    arg1 = i;
  }
  codigo->push_back(instr(op, arg1, arg2, arg3));
}

RNumeric* get_numeric_node(ast* hoja){
  RNumeric* arg=NULL;
  switch(hoja->tipo){
    case f_entero:{
      arg = new RInteger(hoja->entero);
      break;}
    case f_decimal:{
      arg = new RDecimal(hoja->decimal);
      break;}
    default:
      cout << "Error de tipo, el operando no es numerico!" << endl;
      break;
  }
  return arg;
}

RObject* get_abstract_node(ast* hoja){
  RObject* arg=NULL;
  switch(hoja->tipo){
    case f_entero:{
      arg = new RInteger(hoja->entero);
      break;}
    case f_decimal:{
      arg = new RDecimal(hoja->decimal);
      break;}
    case f_string :
      arg = new RString(hoja->str);
      break;
    case f_bool :
      arg = new RBool(hoja->booleano);
      break;
    default:
      cout << "Error de tipo, el operando no es correcto!" << endl;
      break;
  }
  return arg;
}

void generar_elsif(ast* nodo, std::list<Instruccion*> *codigo){
  /*
   * h1 - cond
   * h2 - cuerpo if
   * h3 - elsif -optional
   *
   * */
  if (nodo == NULL)
    return;
  codigo->push_back(instr(ELSIFCOND));
  decidir_nodo(nodo->h1, codigo);
  RObject* cond = codigo->back()->arg1;
  codigo->push_back(instr(ELSIF, cond));
  generar_compstmt(nodo->h2->stmt_list, codigo);
  generar_elsif(nodo->h3, codigo);
}

void generar_while(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_string(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_entero(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_decimal(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_bool(ast* nodo, std::list<Instruccion*> *codigo){}
void generar_puts(ast* nodo, std::list<Instruccion*> *codigo){
  RObject * arg1;
  if (nodo_hoja(nodo->h1)){ // no preciso variable temporal
    ast* hoja = nodo->h1;
    switch(hoja->tipo){
      case f_string:
        cout << "hoja string" << endl;
        arg1= new RString(hoja->str);
        break;
      case f_entero:
        arg1= (new RInteger(hoja->entero))->to_s();
        break;
      case f_decimal:
        arg1 = (new RDecimal(hoja->decimal))->to_s();
        break;
      case f_bool:
        arg1 = (new RBool(hoja->booleano))->to_s();
        break;
    }
  } else {
    decidir_nodo(nodo->h1, codigo);
    cout << "last op " << codigo->back()->op << endl;
    arg1 = codigo->back()->arg1;
  }
  Instruccion* i = new Instruccion;
  i->op = PUTS;
  i->arg1 = arg1;
  codigo->push_back(i);
}

void generar_op_booleana(enum code_ops op, ast* nodo, list<Instruccion*>* codigo){
  RObject* arg2, *arg3, *arg1;
  arg3=NULL;
  if (nodo_hoja(nodo->h1)){ // no preciso variable temporal
    arg2 = get_abstract_node(nodo->h1);
  } else {
    decidir_nodo(nodo->h1, codigo);
    arg2 = (RNumeric*)codigo->back()->arg1;
  }
  if (op != NOT && op != TOBOOL){
    if (nodo_hoja(nodo->h2)){ // no preciso variable temporal
      arg3 = get_abstract_node(nodo->h2);
    } else {
      decidir_nodo(nodo->h2, codigo);
      arg3 = (RNumeric*)codigo->back()->arg1;
    }
  }

  codigo->push_back(instr(op, new RBool(), arg2, arg3));
}

bool nodo_hoja(ast* nodo){
  return (nodo->tipo == f_string || nodo->tipo == f_entero || nodo->tipo == f_decimal || nodo->tipo == f_bool);
}

Instruccion* instr(enum code_ops op){
  Instruccion* inst = new Instruccion;
  inst->op = op;
  return inst;
}

Instruccion* instr(enum code_ops op, RObject* arg1){
  Instruccion* inst = instr(op);
  inst->arg1=arg1;
  return inst;
}

Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2){
  Instruccion* inst = instr(op, arg1);
  inst->arg2=arg2;
  return inst;
}

Instruccion* instr(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3){
  Instruccion* inst = instr(op, arg1, arg2);
  inst->arg3=arg3;
  return inst;
}

void generar_gets(list<Instruccion*>* codigo){
  codigo->push_back(instr(GETS, new RString()));
}

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

void printList(list<ast*> *stmt_list){ list<ast*>::iterator it;
  for (it=stmt_list->begin(); it != stmt_list->end(); it++)
    printTree(*it);
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