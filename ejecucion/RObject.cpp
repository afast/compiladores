#include <iostream>
#include <sstream>

#include "RObject.h"
#include "RInteger.h"
#include "RString.h"
#include "RBool.h"
#include "memory.h"

RObject::RObject(){}

RObject::RObject(bool nil){
  if (nil){
    this->object_id=4;
    this->type = RNIL;
  }
  new_object_pointer(this);
}

bool RObject::is_numeric(){
  return type == RNUMERIC || type == RINT;
}

bool RObject::is_string(){
  return type == RSTRING;
}

bool RObject::is_int(){
  return type == RINT;

}

bool RObject::is_decimal(){
  return type == RNUMERIC;

}

bool RObject::is_array(){
  return type == RARRAY;

}

bool RObject::is_command(){
  return type == RCOMMAND;

}

bool RObject::is_nil(){
  return type == RNIL;
}


RInteger *RObject::objectId(){
  RInteger *res;
  if (object_id != 0)
    res = new RInteger(object_id);
  else {
    long int id;
    std::stringstream s;
    s << (void*)this;
    s >> std::hex >> id;
    object_id = id;
    res = new RInteger(id);
  }
  return res;
}

RString *RObject::get_class(){
  return new RString("nil");
}

RString* RObject::to_s(){
  return new RString("");
}

bool RObject::respond_to(RString *method){
  bool res = *method->getValue() == "object_id" || *method->getValue() == "class" || *method->getValue() == "respond_to?";
  return res;
}
