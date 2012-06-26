#include <iostream>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <cmath>

#include "stack.h"
#include "base.h"
#include "memory.h"
#include "RInteger.h"
#include "RDecimal.h"
#include "RNumeric.h"
#include "RString.h"
#include "RBool.h"
class RString;
using namespace std;

set<string> tsimbolos;
unordered_map<string, list<Instruccion*> *> functions;
//unordered_map<string, RObject*> vTemporales;

unordered_map<string, RObject*> global_variables; // las variables deben agregarse a este hash variables["nombre"] = RObject*
unordered_map<string, list<Instruccion*>*> global_methods; // los metodos globales se guardan aqui methods["nombre"] = list<Instruccion *>*
unordered_map<string, RObject*>* current_stack;
list<unordered_map<string, RObject*>*> scope_stack;
stack<bool> cond_stack;
stack<list<Instruccion *>::iterator> while_stack;

//RObject *getValue(string* key){
//	return vTemporales[*key];
//}

void initializer(){
  // Stack inicial
  scope_stack.push_back(new unordered_map<string, RObject*>);
  current_stack = scope_stack.back();
}

void clean_up(){
  free_memory();
  list<unordered_map<string, RObject*>*>::iterator it;
  for (it=scope_stack.begin(); it != scope_stack.end(); it++)
    delete *it;
}

void ejecutar(list<Instruccion*> *codigo) {
  list<Instruccion *>::iterator it = codigo->begin();
  Instruccion *ri;
  cout << "Excecution started!" << endl;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : cout << "Fin ejecución" << endl; break;
      case PUTS  : puts(ri->arg1->to_s());
        break;
      case GETS  : gets((RString *)ri->arg1); break;
      case ADD   : 
        if (((RNumeric*)ri->arg1)->es_int()){
          ((RInteger*)ri->arg1)->setValue(((RInteger*)ri->arg2)->getValue() + ((RInteger*)ri->arg3)->getValue());
        }else
          ((RDecimal*)ri->arg1)->setValue(((RNumeric*)ri->arg2)->getDecimalValue() + ((RNumeric*)ri->arg3)->getDecimalValue());
        break;
      case OBJID : if (ri->arg1 != NULL) *((RInteger*)ri->arg1) = getDir(ri->arg2); break;
      case MULT : 
        if (((RNumeric*)ri->arg1)->es_int())
          ((RInteger*)ri->arg1)->setValue(((RInteger*)ri->arg2)->getValue() * ((RInteger*)ri->arg3)->getValue());
        else
          ((RDecimal*)ri->arg1)->setValue(((RNumeric*)ri->arg2)->getDecimalValue() * ((RNumeric*)ri->arg3)->getDecimalValue());
        break;
      case SUB :
        if (((RNumeric*)ri->arg1)->es_int())
          ((RInteger*)ri->arg1)->setValue(((RInteger*)ri->arg2)->getValue() - ((RInteger*)ri->arg3)->getValue());
        else
          ((RDecimal*)ri->arg1)->setValue(((RNumeric*)ri->arg2)->getDecimalValue() - ((RNumeric*)ri->arg3)->getDecimalValue());
        break;
      case DIV :
        if (((RNumeric*)ri->arg1)->es_int())
          ((RInteger*)ri->arg1)->setValue(((RInteger*)ri->arg2)->getValue() - ((RInteger*)ri->arg3)->getValue());
        else
          ((RDecimal*)ri->arg1)->setValue(((RNumeric*)ri->arg2)->getDecimalValue() - ((RNumeric*)ri->arg3)->getDecimalValue());
        break;
      case POW :
        if (((RNumeric*)ri->arg1)->es_int())
          ((RInteger*)ri->arg1)->setValue(pow(((RInteger*)ri->arg2)->getValue(), ((RInteger*)ri->arg3)->getValue()));
        else
          ((RDecimal*)ri->arg1)->setValue(pow(((RNumeric*)ri->arg2)->getDecimalValue(), ((RNumeric*)ri->arg3)->getDecimalValue()));
        break;
      case MOD :
        if (((RNumeric*)ri->arg1)->es_int())
          ((RInteger*)ri->arg1)->setValue(((RInteger*)ri->arg2)->getValue() % ((RInteger*)ri->arg3)->getValue());
        else
          ((RDecimal*)ri->arg1)->setValue(((RNumeric*)ri->arg2)->mod((RNumeric*)ri->arg3));
        break;
      case IF : 
        if (!((RBool*)ri->arg1)->getValue())
          it = descartar_if(it);
        cond_stack.push(((RBool*)ri->arg1)->getValue());
        break;
      case ELSIF : if (!((RBool*)ri->arg1)->getValue()) it = descartar_if(it); else { cond_stack.pop(); cond_stack.push(((RBool*)ri->arg1)->getValue());} break;
      case ELSIFCOND : if (cond_stack.top()) it = descartar_hasta_end(it); break;
      case ELSE : if (cond_stack.top()) it = descartar_hasta_end(it); break;
      case END : cond_stack.pop(); break;
      case WHILE : std::cout << "entro: " << ((RBool*)ri->arg1)->getValue() << std::endl; if (((RBool*)ri->arg1)->getValue()) while_stack.push(it); else it=descartar_whileend(it); break;
      case WHILEEND : std::cout << "entro2: " << ((RBool*)ri->arg1)->getValue() << std::endl; if (((RBool*)ri->arg1)->getValue()) it = while_stack.top(); else while_stack.pop(); break;
      case AND :
        ((RBool*)ri->arg1)->setValue(((RBool*)ri->arg2)->getValue() && ((RBool*)ri->arg3)->getValue());
        break;
      case OR :
        ((RBool*)ri->arg1)->setValue(((RBool*)ri->arg2)->getValue() || ((RBool*)ri->arg3)->getValue());
        break;
      case NOT :
        ((RBool*)ri->arg1)->setValue(!((RBool*)ri->arg2)->getValue());
        break;
      case G :
        ((RBool*)ri->arg1)->setValue(mayor(ri->arg2, ri->arg3)->getValue());
        break;
      case GE :
        ((RBool*)ri->arg1)->setValue(mayor_igual(ri->arg2, ri->arg3)->getValue());
        break;
      case L  :
        ((RBool*)ri->arg1)->setValue(menor(ri->arg2, ri->arg3)->getValue());
        break;
      case LE :
        ((RBool*)ri->arg1)->setValue(menor_igual(ri->arg2, ri->arg3)->getValue());
        break;
      case EQ :
        ((RBool*)ri->arg1)->setValue(igual(ri->arg2, ri->arg3)->getValue());
        break;
      case NEQ :
        ((RBool*)ri->arg1)->setValue(!igual(ri->arg2, ri->arg3)->getValue());
        break;
      case TOBOOL :
        ((RBool*)ri->arg1)->setValue(extraer_bool(ri->arg2));
        break;
    }
  } while (ri->op != FIN);

  for (it=codigo->begin(); it != codigo->end(); it++)
    delete *it;
  clean_up();
}

void add_symbol(char *name) {
  tsimbolos.insert(name);
}

RObject *get_variable(char *name){ //aca hay q considerar el tema del scope?
  list<unordered_map<string, RObject*>*>::reverse_iterator rit;
  //unordered_map<string, Instruccion*>* stack;
  rit = scope_stack.rbegin();
  RObject *object;
  do {
    object = (**rit)[name];
  } while (rit != scope_stack.rend());
  return global_variables[name];
}

void set_variable(char *name, RObject* var){ //aca hay q considerar el tema del scope?
  global_variables[name]= var;
}

void add_global_function(char* name, list<Instruccion*>* codigo){
  global_methods[name] = codigo;
}

void new_scope(){
  current_stack = new unordered_map<string, RObject*>;
  scope_stack.push_back(current_stack);
}

void pop_stack(){
  scope_stack.pop_back();
  current_stack = scope_stack.back();
}

list<Instruccion*>::iterator descartar_if(list<Instruccion*>::iterator it) { // caso if false
  Instruccion *ri = *it;
  while (ri->op != ELSIF && ri->op != ELSIFCOND && ri->op != ELSE && ri->op != END) {
    if (ri->op == IF || ri->op == DO || ri->op == IF)
      it = descartar_hasta_end(++it);
    ri = *(++it);
  }
  return it;
}

list<Instruccion*>::iterator descartar_hasta_end(list<Instruccion*>::iterator it){
  Instruccion *ri = *it;
  while (ri->op != END) {
    if (ri->op == IF || ri->op == DO || ri->op == IF)
      it = descartar_hasta_end(++it);
    ri = *(++it);
  }
  return it;
}

std::list<Instruccion*>::iterator descartar_whileend(std::list<Instruccion*>::iterator it){
  Instruccion *ri = *it;
std::cout <<"entre a descartar "<< std::endl;
  while (ri->op != WHILEEND) {
    ri = *(++it);
	std::cout <<"descarte: "<< std::endl;
  }
  return ++it;
}

Instruccion *nuevaInst(enum code_ops op, RObject* arg1, RObject* arg2, RObject* arg3){
  Instruccion *inst = new Instruccion;
  inst->op = op;
  inst->arg1 = arg1;
  inst->arg2 = arg2;
  inst->arg3 = arg3;
  return inst;
}

void decimal_add(RDecimal* arg1, RNumeric* arg2, RNumeric* arg3){
  if (arg2->es_int())
    arg1->setValue(((RInteger*)arg2)->getValue() + ((RDecimal*)arg3)->getValue());
  else
    arg1->setValue(((RDecimal*)arg2)->getValue() + ((RInteger*)arg3)->getValue());
}
