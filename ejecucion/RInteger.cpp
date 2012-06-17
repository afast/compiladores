#include "RInteger.h"
#include "RBool.h"
#include "RString.h"

RInteger::RInteger(){this->value=0;}

RInteger::RInteger(long int integer){
  this->value = integer;
}

long int RInteger::getValue(){
  return this->value;
}
//RInteger *object_id(); use parent method
RString* RInteger::get_class(){
  return new RString("Integer");
}

bool  RInteger::respond_to(RString *method){
  return RObject::respond_to(method);
}

bool  RInteger::operator== (RInteger param){
  return new RBool(this->value == param.getValue());
}

bool  RInteger::operator== (long int param){
  return new RBool(this->value == param);
}

long int RInteger::operator= (RInteger param){
  return param.value;
}

RString* RInteger::to_s(){
  return new RString(this);
}
