#include <iostream>
#include <list>

#include "memory.h"
#include "RString.h"
#include "RInteger.h"
#include "RDecimal.h"
#include "RClass.h"
#include "RBool.h"
#include "RArray.h"

std::list<RString*> strings;
std::list<RInteger*> integers;
std::list<RDecimal*> decimals;
std::list<RClass*> classes;
std::list<RBool*> booleans;
std::list<RArray*> arrays;
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

void free_memory(){
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
}
