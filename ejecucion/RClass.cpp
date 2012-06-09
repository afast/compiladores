#include "RClass.h"
#include "RString.h"
#include "RBool.h"

RClass::RClass(const char* param){
  init(new RString(param));
}

RClass::RClass(std::string* param){
  init(new RString(param));
}

RClass::RClass(RString* param){
  init(param);
}

void RClass::init(RString* param){
  this->name = param;
}

RString* RClass::get_class(){
  return name;
}

RBool* RClass::respond_to(RString *method){
  RBool *res = RObject::respond_to(method);
  if (!res->getValue()) {
    std::list<RString*>::iterator it = method_names.begin();
    do {
      res = **it == *method;
    } while(it++ != method_names.end() && !res->getValue());
  }
  return res;
}

void RClass::add_method(std::string* method, std::list<Instruccion*> *codigo){
  add_method(new RString(method), codigo);
}

void RClass::add_method(RString* method, std::list<Instruccion*> *codigo){
  method_names.push_back(method);
  methods[*(method->getValue())] = codigo;
}
