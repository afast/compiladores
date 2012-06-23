#include "RArray.h"
#include "RInteger.h"
#include "RString.h"
#include "RBool.h"
#include "memory.h"

RArray::RArray(){
  nextSize = 20;
  value = new RObject*[10];
  arrayLength = 0;
}

RArray::RArray(RArray *arg){
  nextSize = (arg->size()->getValue() % 10)*10 + 10;
  value = new RObject*[nextSize];
  nextSize += 10;
  arrayLength = arg->size()->getValue();
  for (int i=0; i<arrayLength; i++)
    value[i] = (*arg)[i];
}

RArray::~RArray(){
  delete this->value;
}

RObject **RArray::getValue(){
  return value;
}

RInteger *RArray::size(){
  RInteger *res = new RInteger(arrayLength);
  new_pointer(res);
  return res;
}

RInteger *RArray::length(){
  RInteger *res = new RInteger(arrayLength);
  new_pointer(res);
  return res;
}

RString *RArray::get_class(){
  RString *clase = new RString("Array");
  new_pointer(clase);
  return clase;
}

bool RArray::respond_to(RString *method){
  return RObject::respond_to(method);
}

bool RArray::operator== (RArray param){
  bool res;
  if (param.size() != this->size())
    res = false;
  else if (param.size() == 0)
    res = true;
  else {
    int i=0;
    res = false;
    while (i < param.size()->getValue() && !res) {
      RObject object1, object2;
      object1 = *(param[i]);
      object2 = *(value[i]);
      if (object1.get_class() == object2.get_class() && object1 == object2)
        res = true;
    }
  }
  return res;
}

RObject* RArray::operator[] (int n){
  return value[n];
}

RObject* RArray::operator[] (RInteger param){
  return value[param.getValue()];
}

RObject* RArray::operator[] (RInteger *param){
  return (*this)[*param];
}
