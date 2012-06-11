#include "RBool.h"
#include "RString.h"

bool RBool::getValue(){
  return this->value;
}

RBool::RBool(){}

RBool::RBool(bool arg){
  value = arg;
}

RBool::RBool(RBool *arg){
  value = arg->getValue();
}

RString* RBool::get_class(){
  return new RString("Bool");
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
