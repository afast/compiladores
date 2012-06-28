#include <iostream>
#include <sstream>
#include <string>

#include "RBool.h"
#include "RString.h"
#include "RInteger.h"
#include "RDecimal.h"
#include "memory.h"

RString::RString(){
  str = NULL;
  type = RSTRING;
}

RString::RString(const char *arg){
  this->str = new std::string(arg);
  new_pointer(this);
  type = RSTRING;
}

RString::RString(char *arg){
  this->str = new std::string(arg);
  new_pointer(this);
  type = RSTRING;
}

RString::RString(std::string *arg){
  this->str = new std::string(*arg);
  new_pointer(this);
  type = RSTRING;
}

RString::RString(char *arg, bool cortar_extremos){
  str = new std::string(arg);
  new_pointer(this);
  type = RSTRING;
  if (cortar_extremos){
    str->erase(str->begin());
    str->erase(str->end()-1);
  }
}

RString::RString(RString *arg){
  this->str = new std::string(*arg->getValue());
  new_pointer(this);
  type = RSTRING;
}

RString::RString(RInteger *arg){
  this->str = new std::string();
  std::stringstream s;
  s << arg->getValue();
  s >> *str;
  new_pointer(this);
  type = RSTRING;
}

RString::RString(RDecimal *arg){
  this->str = new std::string();
  std::stringstream s;
  s << arg->getValue();
  s >> *str;
  new_pointer(this);
  type = RSTRING;
}

RString::~RString(){
  delete this->str;
}

RString * RString::get_class(){
  RString* s = new RString("String");
  return s;
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
  if (this->str != NULL)
    delete str;
  str = new std::string(param);
}

void RString::setValue(std::string *param){
  if (this->str != NULL)
    delete str;
  str = param;
}

void RString::setValue(std::string param){
  if (this->str != NULL)
    delete str;
  str = new std::string(param.data());
}

RString* RString::to_s(){
  return this;
}

void RString::setValue(RString * param){
  if (this->str != NULL)
    delete str;
  str = new std::string(*(param->getValue()));
}
