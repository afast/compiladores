#include <iostream>
#include <list>

#include "memory.h"
#include "RString.h"
#include "RInteger.h"
#include "RDecimal.h"
#include "RClass.h"
#include "RBool.h"
#include "RArray.h"
#include "RVariable.h"
#include "RObject.h"

std::list<RString*> strings;
std::list<RVariable*> variables;
std::list<RInteger*> integers;
std::list<RDecimal*> decimals;
std::list<RClass*> classes;
std::list<RBool*> booleans;
std::list<RArray*> arrays;
std::list<RObject*> objects;
void new_pointer(RVariable* obj){
  variables.push_back(obj);
}

void new_pointer(RString* obj){
    strings.push_back(obj);
}

void new_pointer(RInteger* obj){
  integers.push_back(obj);
}

void new_pointer(RDecimal* obj){
  decimals.push_back(obj);
}

void new_pointer(RClass* obj){
  classes.push_back(obj);
}

void new_pointer(RBool* obj){
  booleans.push_back(obj);
}

void new_pointer(RArray* obj){
  arrays.push_back(obj);
}

void new_pointer(RObject* obj){
  switch (obj->type){
    case RNIL :
      objects.push_back(obj);
      break;
    case RVARIABLE :
      variables.push_back((RVariable*)obj);
      break;
    case RSTRING :
      strings.push_back((RString*)obj);
      break;
    case RINT :
      integers.push_back((RInteger*)obj);
      break;
    case RNUMERIC :
      decimals.push_back((RDecimal*)obj);
      break;
    case RCLASS :
      classes.push_back((RClass*)obj);
      break;
    case RBOOL :
      booleans.push_back((RBool*)obj);
      break;
    case RARRAY :
      arrays.push_back((RArray*)obj);
      break;
  }
}

void free_memory(){
  std::list<RVariable*>::iterator itv;
  for (itv=variables.begin(); itv != variables.end(); itv++)
    delete (*itv);
  std::list<RString*>::iterator its;
  for (its=strings.begin(); its != strings.end(); its++)
    delete (*its);
  std::list<RInteger*>::iterator iti;
  for (iti=integers.begin(); iti != integers.end(); iti++)
    delete (*iti);
  std::list<RDecimal*>::iterator itd;
  for (itd=decimals.begin(); itd != decimals.end(); itd++)
    delete (*itd);
  std::list<RClass*>::iterator itc;
  for (itc=classes.begin(); itc != classes.end(); itc++)
    delete (*itc);
  std::list<RBool*>::iterator itb;
  for (itb=booleans.begin(); itb != booleans.end(); itb++)
    delete (*itb);
  std::list<RArray*>::iterator ita;
  for (ita=arrays.begin(); ita != arrays.end(); ita++)
    delete (*ita);
  std::list<RObject*>::iterator ito;
  for (ito=objects.begin(); ito != objects.end(); ito++)
    delete (*ito);
}
