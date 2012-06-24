#include "RClass.h"
#include "RString.h"
#include "RBool.h"
#include "memory.h"

RClass::RClass(const char* param){
  RString *s = new RString(param);
  new_pointer(s);
  init(s);
}

RClass::RClass(std::string* param){
  RString *s = new RString(param);
  new_pointer(s);
  init(s);
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

bool RClass::respond_to(RString *method){
  bool res = RObject::respond_to(method);
  if (!res) {
    std::list<RString*>::iterator it = method_names.begin();
    do {
      res = **it == *method;
    } while(it++ != method_names.end() && !res);
  }
  return res;
}

void RClass::add_method(std::string* method, std::list<Instruccion*> *codigo){
  RString *nombre_metodo = new RString(method);
  new_pointer(nombre_metodo);
  method_names.push_back(nombre_metodo);
  methods[*method] = codigo;
}

void RClass::add_method(RString* method, std::list<Instruccion*> *codigo){
  add_method(method->getValue(), codigo);
}
