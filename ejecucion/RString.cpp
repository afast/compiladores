#include <iostream>
#include <string>

#include "RBool.h"
#include "RString.h"

RString::RString(){
  str = new std::string();
}

RString::RString(const char *arg){
  this->str = new std::string(arg);
}

RString::RString(char *arg){
  this->str = new std::string(arg);
}

RString::RString(std::string *arg){
  this->str = new std::string(*arg);
}

RString::RString(RString *arg){
  this->str = new std::string(*arg->getValue());
}

RString * RString::get_class(){
  return new RString("String");
}

RBool *RString::respond_to(RString *method){
  return RObject::respond_to(method);
}

std::string *RString::getValue(){
  return str;
}

RBool * RString::operator== (RString param) {
  return new RBool(this->str->compare(*param.getValue()) == 0);
}

RBool * RString::operator== (std::string *param) {
  return new RBool(this->str->compare(*param) == 0);
}

RBool * RString::operator== (const char *param) {
  return new RBool(this->str->compare(param) == 0);
}
