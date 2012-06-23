#include "RInteger.h"
#include "RBool.h"
#include "RString.h"
#include "memory.h"

RInteger::RInteger(){}

RInteger::RInteger(long int integer){
  this->value = integer;
}

long int RInteger::getValue(){
  return this->value;
}
//RInteger *object_id(); use parent method
RString* RInteger::get_class(){
  RString *s = new RString("Integer");
  new_pointer(s);
  return s;
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
