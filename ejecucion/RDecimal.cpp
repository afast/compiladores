#include "RDecimal.h"
#include "RBool.h"
#include "RString.h"
#include "memory.h"

RDecimal::RDecimal(){
  this->value=0;
  this->decimal = true;
  this->integer = false;
  new_pointer(this);
}

RDecimal::RDecimal(double decimal){
  this->value = decimal;
  this->decimal = true;
  this->integer = false;
  new_pointer(this);
}

double RDecimal::getValue(){
  return this->value;
}

void RDecimal::setValue(double dec){
  this->value = dec;
}
//RDecimal *object_id(); use parent method
RString* RDecimal::get_class(){
  return new RString("Decimal");
}


bool  RDecimal::respond_to(RString *method){
  return RObject::respond_to(method);
}

bool  RDecimal::operator== (RDecimal param){
  return this->value == param.getValue();
}

bool  RDecimal::operator== (double param){
  return this->value == param;
}

double RDecimal::operator= (RDecimal param){
  return param.value;
}

RString* RDecimal::to_s(){
  return new RString(this);
}
