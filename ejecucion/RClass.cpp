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

RClass::~RClass(){}

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

void RClass::add_method(std::string* method, function_info* codigo){
  method_names.push_back(new RString(method));
  methods[*method] = codigo;
}

void RClass::add_method(RString* method, function_info* codigo){
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

function_info* RClass::get_function_info(RString* method){
  return methods[*method->getValue()];
}

void RClass::set_instance_variable(const char* variable, RObject* value){
  instance_variables[variable] = value;
}

void RClass::set_instance_variable(RString* variable, RObject* value){
  instance_variables[*variable->getValue()] = value;
}

RObject* RClass::get_instance_variable(const char* variable){
  RObject* res=NULL;
  if (instance_variables.find(variable) != instance_variables.end())
    res = instance_variables[variable];
  else {
    res = new RObject();
    instance_variables[variable] = res;
  }
  return res;
}

RObject* RClass::get_instance_variable(RString* variable){
  RObject* res=NULL;
  if (instance_variables.find(*variable->getValue()) != instance_variables.end())
    res = instance_variables[*variable->getValue()];
  else {
    res = new RObject();
    instance_variables[*variable->getValue()] = res;
  }
  return res;
}
