#include <sstream>
#include <cmath>

#include "base.h"
#include "RString.h"
#include "RInteger.h"
#include "RNumeric.h"
#include "RDecimal.h"
#include "RInteger.h"
#include "RBool.h"
#include "memory.h"

std::unordered_map<std::string, RObject*> vTemporales;

void puts(RString *string_arg) {
  if (string_arg->getValue()->size()>0){
    std::string *str = new std::string(string_arg->getValue()->data());
    while (str->at(str->size()-1) == '\n')
      str->erase(str->size()-1);
    std::cout << str->data() << std::endl;
    delete str;
  } else
    std::cout << string_arg->getValue()->data() << std::endl;
}

/*void puts(RCommand *command) {
  if (command->getValue()->size()>0){
    std::string *str = new std::string(command->getValue()->data());
    while (str->at(str->size()-1) == '\n')
      str->erase(str->size()-1);
    std::cout << str->data() << std::endl;
    delete str;
  } else
    std::cout << command->getValue()->data() << std::endl;
}*/

void gets(RString *string_arg) {
  std::string *str = new std::string();
  getline(std::cin, *str);
  str->push_back('\n'); // Ruby lee el string incluido el fin de linea
  string_arg->setValue(str);
}

void mod(RString *arg1, RString *arg2, RString *arg3) {
  RInteger *op1 = (RInteger *)vTemporales[*(arg1->getValue())];
  RInteger *op2 = (RInteger *)vTemporales[*(arg2->getValue())];
  vTemporales[*(arg3->getValue())] = new RInteger(op1->getValue() % op2->getValue());
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

RBool* mayor(RObject* arg1, RObject* arg2){
  RBool* res = NULL;
  if (arg1->type != arg2->type)
    error_generando("No se puede comparar objetos de tipo diferente");
  else{
    bool resultado;
    switch(arg1->type){
      case RNUMERIC:
        resultado = ((RNumeric*)arg1)->getDecimalValue() > ((RNumeric*)arg2)->getDecimalValue();
        break;
      case RINT:
        resultado = ((RNumeric*)arg1)->getDecimalValue() > ((RNumeric*)arg2)->getDecimalValue();
        break;
      case RBOOL:
        resultado = ((RBool*)arg1)->getValue() > ((RBool*)arg2)->getValue();
        break;
      case RSTRING:
        resultado = *((RString*)arg1)->getValue() > *((RString*)arg2)->getValue();
        break;
    }
    res = new RBool(resultado);
  }
  return res;
}

RBool* mayor_igual(RObject* arg1, RObject* arg2){
  RBool* res = NULL;
  if (arg1->type != arg2->type)
    error_generando("No se puede comparar objetos de tipo diferente");
  else{
    bool resultado;
    switch(arg1->type){
      case RNUMERIC:
        resultado = ((RDecimal*)arg1)->getValue() >= ((RDecimal*)arg2)->getValue();
        break;
      case RINT:
        resultado = ((RInteger*)arg1)->getValue() >= ((RInteger*)arg2)->getValue();
        break;
      case RBOOL:
        resultado = ((RBool*)arg1)->getValue() >= ((RBool*)arg2)->getValue();
        break;
      case RSTRING:
        resultado = *((RString*)arg1)->getValue() >= *((RString*)arg2)->getValue();
        break;
    }
    res = new RBool(resultado);
  }

  return res;
}

RBool* menor(RObject* arg1, RObject* arg2){
  RBool* res = mayor_igual(arg1, arg2);
  res->setValue(!res->getValue());
  return res;
}

RBool* menor_igual(RObject* arg1, RObject* arg2){
  RBool* res = mayor(arg1, arg2);
  res->setValue(!res->getValue());
  return res;
}

RBool* igual(RObject* arg1, RObject* arg2){
  RBool* res = NULL;
  if (arg1->type != arg2->type){
    error_generando("No se puede comparar objetos de tipo diferente");
    res = new RBool(false);
  }else {
    bool resultado;
    switch(arg1->type){
      case RNUMERIC:
        resultado = ((RNumeric*)arg1)->getDecimalValue() == ((RNumeric*)arg2)->getDecimalValue();
        break;
      case RINT:
        resultado = ((RInteger*)arg1)->getValue() == ((RInteger*)arg2)->getValue();
        break;
      case RBOOL:
        resultado = ((RBool*)arg1)->getValue() == ((RBool*)arg2)->getValue();
        break;
      case RSTRING:
        resultado = *((RString*)arg1)->getValue() == *((RString*)arg2)->getValue();
        break;
      case RNIL:
        resultado = (arg1->type == arg2->type);
        break;
    }
    res = new RBool(resultado);
  }

  return res;
}

bool extraer_bool(RObject* arg){
  return arg->type != RNIL && (arg->type != RBOOL || ((RBool*)arg)->getValue());
}

void error_generando(const char * msj){
  std::cout << "Error generando codigo!" << std::endl;
  std::cout << msj << std::endl;
}
