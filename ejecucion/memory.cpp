#include <iostream>
#include <list>

#include "stack.h"
#include "memory.h"
#include "RString.h"
#include "RInteger.h"
#include "RDecimal.h"
#include "RClass.h"
#include "RBool.h"
#include "RArray.h"
#include "RVariable.h"
#include "RObject.h"

std::list<RString*> mstrings;
std::list<RVariable*> mvariables;
std::list<RInteger*> mintegers;
std::list<RDecimal*> mdecimals;
std::list<RClass*> mclasses;
std::list<RBool*> mbooleans;
std::list<RArray*> marrays;
std::list<function_info*> mfunctions;
void new_pointer(RVariable* obj){
  mvariables.push_back(obj);
}

void new_pointer(RString* obj){
    mstrings.push_back(obj);
}

void new_pointer(RInteger* obj){
  mintegers.push_back(obj);
}

void new_pointer(RDecimal* obj){
  mdecimals.push_back(obj);
}

void new_pointer(RClass* obj){
  mclasses.push_back(obj);
}

void new_pointer(RBool* obj){
  mbooleans.push_back(obj);
}

void new_pointer(RArray* obj){
  marrays.push_back(obj);
}

void new_pointer(function_info_t* funcion){
  mfunctions.push_back(funcion);
}

void free_memory(){
  std::list<RVariable*>::iterator itv;
  for (itv=mvariables.begin(); itv != mvariables.end(); itv++)
    delete (*itv);
  std::list<RString*>::iterator its;
  for (its=mstrings.begin(); its != mstrings.end(); its++)
    delete (*its);
  std::list<RInteger*>::iterator iti;
  for (iti=mintegers.begin(); iti != mintegers.end(); iti++)
    delete (*iti);
  std::list<RDecimal*>::iterator itd;
  for (itd=mdecimals.begin(); itd != mdecimals.end(); itd++)
    delete (*itd);
  std::list<RClass*>::iterator itc;
  for (itc=mclasses.begin(); itc != mclasses.end(); itc++)
    delete (*itc);
  std::list<RBool*>::iterator itb;
  for (itb=mbooleans.begin(); itb != mbooleans.end(); itb++)
    delete (*itb);
  std::list<RArray*>::iterator ita;
  for (ita=marrays.begin(); ita != marrays.end(); ita++)
    delete (*ita);
  std::list<function_info*>::iterator itf;
  std::list<Instruccion*>::iterator iter;
  for (itf=mfunctions.begin(); itf != mfunctions.end(); itf++){
    for (iter=(*itf)->codigo->begin(); iter != (*itf)->codigo->end(); iter++)
      delete *iter;
    delete (*itf)->codigo;
    delete *itf;
  }
}
