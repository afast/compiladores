#include <iostream>
#include <sstream>

#include "RObject.h"
#include "RInteger.h"
#include "RString.h"
#include "RBool.h"

RObject::RObject(){
  this->object_id=0;
  this->type = ROBJECT;
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
  return new RString("Object");
}

RString* RObject::to_s(){
  return this->get_class();
}

bool RObject::respond_to(RString *method){
  bool res = *method == "object_id" || *method == "class" || *method == "respond_to?";
  return res;
}

bool RObject::operator== (RObject param) {
  return this->objectId() == param.objectId();
}


