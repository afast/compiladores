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
#include "RVariable.h"

using namespace std;

set<string> tsimbolos;
unordered_map<string, list<Instruccion*> *> functions;
//unordered_map<string, RObject*> vTemporales;

unordered_map<string, RObject*> *global_variables= new unordered_map<string, RObject*>; // las variables deben agregarse a este hash variables["nombre"] = RObject*
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
  RObject *arg1, *arg2, *arg3;
  bool set_tmp;
  cout << "Excecution started!" << endl;
  do {
    ri = *it++;
    arg1 = ri->arg1; arg2 = ri->arg2; arg3 = ri->arg3;
    if (arg1 != NULL && arg1->type == RVARIABLE)
      arg1 = get_variable(((RVariable*)arg1)->getValue()->data());
    if (arg2 != NULL && arg2->type == RVARIABLE)
      arg2 = get_variable(((RVariable*)arg2)->getValue()->data());
    if (arg3 != NULL && arg3->type == RVARIABLE)
      arg3 = get_variable(((RVariable*)arg3)->getValue()->data());
    set_tmp = (arg1 != NULL && arg1->type == RNIL);
    switch (ri->op) {
      case FIN   : cout << "Fin ejecución" << endl; break;
      case PUTS  : puts(arg1->to_s());
        break;
      case GETS  : gets((RString *)ri->arg1); break;
      case ADD   :
        if (arg2->is_numeric() && arg3->is_numeric()){
          if (((RNumeric*)arg1)->es_int()){
            if (set_tmp)
              arg1 = new RInteger();
            ((RInteger*)arg1)->setValue(((RInteger*)arg2)->getValue() + ((RInteger*)arg3)->getValue());
          }else{
            if (set_tmp)
              arg1 = new RDecimal();
            ((RDecimal*)arg1)->setValue(((RNumeric*)arg2)->getDecimalValue() + ((RNumeric*)arg3)->getDecimalValue());
          }
        }else{
          if (arg2->type == arg3->type && arg2->type == RSTRING){
            if (set_tmp)
              arg1 = new RString();
            ((RString*)arg1)->setValue(*((RString*)arg2)->getValue() + *((RString*)arg3)->getValue());
          }else
            cout << "Error de tipos, no se puede sumar " << *arg2->get_class()->getValue() << " con " << *arg3->get_class()->getValue() << endl;
        }
        if (set_tmp)
          set_global_variable(((RVariable*)ri->arg1)->getValue(), arg1);
        break;
      case OBJID : if (arg1 != NULL) *((RInteger*)arg1) = getDir(arg2); break;
      case MULT : 
        if (((RNumeric*)arg1)->es_int())
          ((RInteger*)arg1)->setValue(((RInteger*)arg2)->getValue() * ((RInteger*)arg3)->getValue());
        else
          ((RDecimal*)arg1)->setValue(((RNumeric*)arg2)->getDecimalValue() * ((RNumeric*)arg3)->getDecimalValue());
        break;
      case SUB :
        if (((RNumeric*)arg1)->es_int())
          ((RInteger*)arg1)->setValue(((RInteger*)arg2)->getValue() - ((RInteger*)arg3)->getValue());
        else
          ((RDecimal*)arg1)->setValue(((RNumeric*)arg2)->getDecimalValue() - ((RNumeric*)arg3)->getDecimalValue());
        break;
      case DIV :
        if (((RNumeric*)arg1)->es_int())
          ((RInteger*)arg1)->setValue(((RInteger*)arg2)->getValue() - ((RInteger*)arg3)->getValue());
        else
          ((RDecimal*)arg1)->setValue(((RNumeric*)arg2)->getDecimalValue() - ((RNumeric*)arg3)->getDecimalValue());
        break;
      case POW :
        if (((RNumeric*)arg1)->es_int())
          ((RInteger*)arg1)->setValue(pow(((RInteger*)arg2)->getValue(), ((RInteger*)arg3)->getValue()));
        else
          ((RDecimal*)arg1)->setValue(pow(((RNumeric*)arg2)->getDecimalValue(), ((RNumeric*)arg3)->getDecimalValue()));
        break;
      case MOD :
        if (((RNumeric*)arg1)->es_int())
          ((RInteger*)arg1)->setValue(((RInteger*)arg2)->getValue() % ((RInteger*)arg3)->getValue());
        else
          ((RDecimal*)arg1)->setValue(((RNumeric*)arg2)->mod((RNumeric*)arg3));
        break;
      case IF : 
        if (!((RBool*)arg1)->getValue())
          it = descartar_if(it);
        cond_stack.push(((RBool*)arg1)->getValue());
        break;
      case ELSIF : if (!((RBool*)arg1)->getValue()) it = descartar_if(it); else { cond_stack.pop(); cond_stack.push(((RBool*)arg1)->getValue());} break;
      case ELSIFCOND : if (cond_stack.top()) it = descartar_hasta_end(it); break;
      case ELSE : if (cond_stack.top()) it = descartar_hasta_end(it); break;
      case END : cond_stack.pop(); break;
      case WHILE : if (((RBool*)arg1)->getValue()) while_stack.push(it); else it=descartar_whileend(it); break;
      case WHILEEND : if (((RBool*)arg1)->getValue()) it = while_stack.top(); else while_stack.pop(); break;
      case AND :
        ((RBool*)arg1)->setValue(((RBool*)arg2)->getValue() && ((RBool*)arg3)->getValue());
        break;
      case OR :
        ((RBool*)arg1)->setValue(((RBool*)arg2)->getValue() || ((RBool*)arg3)->getValue());
        break;
      case NOT :
        ((RBool*)arg1)->setValue(!((RBool*)arg2)->getValue());
        break;
      case G :
        ((RBool*)arg1)->setValue(mayor(arg2, arg3)->getValue());
        break;
      case GE :
        ((RBool*)arg1)->setValue(mayor_igual(arg2, arg3)->getValue());
        break;
      case L  :
        ((RBool*)arg1)->setValue(menor(arg2, arg3)->getValue());
        break;
      case LE :
        ((RBool*)arg1)->setValue(menor_igual(arg2, arg3)->getValue());
        break;
      case EQ :
        ((RBool*)arg1)->setValue(igual(arg2, arg3)->getValue());
        break;
      case NEQ :
        ((RBool*)arg1)->setValue(!igual(arg2, arg3)->getValue());
        break;
      case TOBOOL :
        ((RBool*)arg1)->setValue(extraer_bool(arg2));
        break;
      case GETV : // Evaluar variable o metodo?
        //ri->arg1 = get_variable((RString*)arg2);
        break;
      case PUTV :
        set_variable((RString*)arg1, arg2);
        break;
      case ASGN:
        set_variable((RString*)arg1, arg2);
        break;
    }
  } while (ri->op != FIN);

  clean_up();
  for (it=codigo->begin(); it != codigo->end(); it++)
    delete *it;
}

void add_symbol(char *name) {
  tsimbolos.insert(name);
}

RObject *get_variable(const char *name){ //aca hay q considerar el tema del scope?
  list<unordered_map<string, RObject*>*>::reverse_iterator rit;
  //unordered_map<string, Instruccion*>* stack;
  rit = scope_stack.rbegin();
  RObject *object;
  do {
    object = (**rit)[name];
    rit++;
  } while (object == NULL && rit != scope_stack.rend());
  if (object == NULL)
    object = (*global_variables)[name];
  if (object == NULL)
    cout << "Warning, variable is null!" << endl;
  return object;
}

RObject* get_variable(RString* str){
  return get_variable(str->getValue()->data());
}

void set_variable(const char *name, RObject* var){ //aca hay q considerar el tema del scope?
  (*current_stack)[name] = var;
}

void set_global_variable(string *name, RObject* var){ //aca hay q considerar el tema del scope?
  (*global_variables)[name->data()] = var;
}

void set_variable(RString* str, RObject* var){ //aca hay q considerar el tema del scope?
  set_variable(str->getValue()->data(), var);
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
  while (ri->op != WHILEEND) {
    ri = *(++it);
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
