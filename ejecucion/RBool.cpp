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

RBool* RBool::respond_to(RString *method){
  return RObject::respond_to(method);
}

RBool RBool::operator== (RBool param){
  return RBool(*this == param);
}

RBool RBool::operator|| (RBool param){
  return RBool(*this || param);
}

RBool RBool::operator&& (RBool param){
  return RBool(*this && param);
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
