#include "RDecimal.h"
#include "RBool.h"
#include "RString.h"
#include "memory.h"

RDecimal::RDecimal(){this->value=0;}

RDecimal::RDecimal(double decimal){
  this->value = decimal;
}

double RDecimal::getValue(){
  return this->value;
}
//RDecimal *object_id(); use parent method
RString* RDecimal::get_class(){
  RString *s = new RString("Decimal");
  new_pointer(s);
  return s;
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
  RString *s = new RString(this);
  new_pointer(s);
  return s;
}
