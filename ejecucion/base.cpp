#include <sstream>

#include "base.h"
#include "RString.h"
#include "RInteger.h"
#include "Util.h"
#include <math.h>

std::unordered_map<std::string, RObject*> vTemporales;

void puts(RString *string_arg) {
  RInteger* value = (RInteger *)vTemporales[*(string_arg->getValue())];
  //===============================================================
  // EL PUTS DEBE ESTAR SOBRECARGADO
  //===============================================================
		RString* tmp = new RString(Util::intToString(value->getValue()));

  std::string *str = new std::string(tmp->getValue()->data());
  while (str->at(str->size()-1) == '\n')
    str->erase(str->size()-1);
  std::cout << str->data() << std::endl;

  delete str;
}

void gets(RString *string_arg) {
  std::string *str = new std::string();
  if (string_arg->getValue() != NULL)
    delete string_arg->getValue();
  getline(std::cin, *str);
  str->push_back('\n'); // Ruby lee el string incluido el fin de linea
  string_arg->setValue(str);
}

void add(RString *arg1, RString *arg2, RString *arg3) {
std::cout << "------------1111111111111111------>   " << std::endl;
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];

  vTemporales[*(arg3->getValue())] = *op1 + *op2;
	std::cout << "------------------>   " << std::endl;
}

void mult(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(op1->getValue() * op2->getValue());
}

void sub(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(op1->getValue() - op2->getValue());
}

void div(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(op1->getValue() / op2->getValue()); /*FALTA CONTROLAR DIVISION ENTRE 0, no se si es aca*/
}

void pow(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(pow(op1->getValue(), op2->getValue())); 
}

void mod(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(op1->getValue() % op2->getValue());
}


void assign_tmp(RString *name, RObject * value){
	vTemporales[*(((RString *)name)->getValue())] = value;
std::cout << "-QQQQQQQQQ----------------->   " << ((RInteger *)vTemporales[*(((RString *)name)->getValue())])->getValue() << std::endl;
}

long int getDir(void* p){
  long int id;
  std::stringstream s, sp;
  std::string str;
  sp << (void*)p;
  sp >> str;
  s << (void*)p;
  s >> std::hex >> id;
  std::cout << str << std::endl;
  std::cout << "check " << id << std::endl;
  return id;
}

void init(){
  //Default methods
  
}
