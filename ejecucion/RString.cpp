#include <iostream>
#include <sstream>
#include <string>

#include "RBool.h"
#include "RString.h"
#include "RInteger.h"

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

RString::RString(RInteger *arg){
  this->str = new std::string();
  std::stringstream s;
  s << arg->getValue();
  s >> *str;
}

RString * RString::get_class(){
  return new RString("String");
}

bool RString::respond_to(RString *method){
  return RObject::respond_to(method);
}

std::string *RString::getValue(){
  return str;
}

bool RString::operator== (RString param) {
  return this->str->compare(*param.getValue()) == 0;
}

bool RString::operator== (std::string *param) {
  return this->str->compare(*param) == 0;
}

bool RString::operator== (const char *param) {
  return this->str->compare(param) == 0;
}

void RString::setValue(const char * param){
  if (this->str == NULL)
    delete str;
  str = new std::string(param);
}

void RString::setValue(std::string *param){
  if (this->str == NULL)
    delete str;
  str = param;
}

void RString::setValue(std::string param){
  if (this->str == NULL)
    delete str;
  str = new std::string(param);
}

void RString::setValue(RString * param){
  if (this->str == NULL)
    delete str;
  str = new std::string(*(param->getValue()));
}
