#include "RBool.h"
#include "RString.h"
#include "memory.h"

bool RBool::getValue(){
  return this->value;
}

RBool::RBool(){new_pointer(this);}

RBool::RBool(bool arg){
  value = arg;
  new_pointer(this);
}

RBool::RBool(RBool *arg){
  value = arg->getValue();
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
