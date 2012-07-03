#include "RBool.h"
#include "RString.h"
#include "memory.h"

bool RBool::getValue(){
  return this->value;
}

void RBool::setValue(bool val){
  this->value = val;
}

void RBool::setValue(RBool* val){
  this->value = val->getValue();
}

RBool::RBool(){
  new_pointer(this);
  type = RBOOL;
}

RBool::RBool(bool arg){
  value = arg;
  new_pointer(this);
  type = RBOOL;
}

RBool::RBool(RBool *arg){
  value = arg->getValue();
  type = RBOOL;
}

RString* RBool::get_class(){
  return new RString("Bool");
}

RString* RBool::to_s(){
  return new RString(this->value ? "true" : "false");
}

bool RBool::respond_to(RString *method){
  return RObject::respond_to(method);
}

bool RBool::operator== (RBool param){
  return *this == param;
}

bool RBool::operator|| (RBool param){
  return *this || param;
}

bool RBool::operator&& (RBool param){
  return *this && param;
}

bool RBool::operator= (RBool param){
  return param.getValue();
}

bool operator&& (RBool param2, bool param1){
  return param1 && param2.getValue();
}

bool operator|| (RBool param2, bool param1){
  return param1 || param2.getValue();
}
