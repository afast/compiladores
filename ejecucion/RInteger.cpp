#include "RInteger.h"
#include "RBool.h"
#include "RString.h"

RInteger::RInteger(){}

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

RBool* RInteger::respond_to(RString *method){
  return RObject::respond_to(method);
}

RBool * RInteger::operator== (RInteger param){
  return new RBool(this->value == param.getValue());
}

RBool * RInteger::operator== (long int param){
  return new RBool(this->value == param);
}
