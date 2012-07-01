#include "RClass.h"
#include "RString.h"
#include "RBool.h"
#include "memory.h"

RClass::RClass(const char* param){
  init(new RString(param));
}

RClass::RClass(std::string* param){
  init(new RString(param));
}

RClass::RClass(RString* param){
  init(param);
}

RClass::~RClass(){
  delete name;
  std::list<RString*>::iterator it;
  std::list<Instruccion*> *codigo;
  std::list<Instruccion*> *nuevo_codigo;
  std::list<Instruccion*>::iterator cod_it;
  for(it=method_names.begin(); it != method_names.end(); it++){
    codigo = methods[*(*it)->getValue()];
    if (codigo != NULL){
      for (cod_it = codigo->begin(); cod_it != codigo->end(); cod_it++){
        if (*cod_it != NULL)
          delete *cod_it;
        *cod_it = NULL;
      }
      delete codigo;
      codigo = NULL;
    }
  }
}

void RClass::init(RString* param){
  this->name = param;
  this->type = RCLASS;
}

RString* RClass::get_class(){
  return name;
}

RString* RClass::to_s(){
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
  method_names.push_back(new RString(method));
  methods[*method] = codigo;
}

void RClass::add_method(RString* method, std::list<Instruccion*> *codigo){
  add_method(method->getValue(), codigo);
}

RClass* RClass::get_instance(){
  RClass* res = new RClass(this->name);
  std::list<RString*>::iterator it;
  std::list<Instruccion*> *codigo;
  std::list<Instruccion*> *nuevo_codigo;
  std::list<Instruccion*>::iterator cod_it;
  for(it=method_names.begin(); it != method_names.end(); it++)
    res->add_method((*it)->getValue(), methods[*(*it)->getValue()]);
  for(auto iter=instance_variables.begin(); iter != instance_variables.end(); iter++)
    res->add_instance_variable(new RString(iter->first.data()));

  return res;
}

void RClass::add_instance_variable(RString* variable){
  instance_variables[*variable->getValue()] = new RObject();
}

void RClass::add_instance_variable(std::string* variable){
  instance_variables[*variable] = new RObject();
}
