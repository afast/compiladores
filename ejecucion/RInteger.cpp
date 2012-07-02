#include "RInteger.h"
#include "RBool.h"
#include "RString.h"
#include "memory.h"

RInteger::RInteger(){
  this->value=0;
  this->integer = true;
  this->decimal = false;
  new_pointer(this);
  type = RINT;
}

RInteger::RInteger(long int integer){
  this->value = integer;
  this->integer = true;
  this->decimal = false;
  new_pointer(this);
  type = RINT;
}

long int RInteger::getValue(){
  return this->value;
}

double RInteger::getDecimalValue(){
  return (double)this->value;
}

void RInteger::setValue(long int val){
  this->value = val;
}

bool  RInteger::respond_to(RString *method){
  return RObject::respond_to(method);
}

bool  RInteger::operator== (RInteger param){
  return this->value == param.getValue();
}

bool  RInteger::operator== (long int param){
  return this->value == param;
}

long int RInteger::operator= (RInteger param){
  return param.value;
}

RString* RInteger::to_s(){
  return new RString(this);
}

RString* RInteger::get_class(){
  return new RString("Integer");;
}
