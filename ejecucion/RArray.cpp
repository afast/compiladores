#include "RArray.h"
#include "RInteger.h"
#include "RString.h"
#include "RBool.h"
#include "memory.h"

RArray::RArray(){
  nextSize = 20;
  value = new RObject*[10];
  arrayLength = 0;
  new_pointer(this);
  type = RARRAY;
}

RArray::RArray(RArray *arg){
  new_pointer(this);
  nextSize = (arg->size()->getValue() % 10)*10 + 10;
  value = new RObject*[nextSize];
  nextSize += 10;
  type = RARRAY;
  arrayLength = arg->size()->getValue();
  for (int i=0; i<arrayLength; i++)
    value[i] = (*arg)[i];
}

RArray::~RArray(){
  delete[] this->value;
}

RObject **RArray::getValue(){
  return value;
}

RInteger *RArray::size(){
  return new RInteger(arrayLength);
}

RString *RArray::to_s(){
  return this->get_class();
}

RInteger *RArray::length(){
  return new RInteger(arrayLength);
}

RString *RArray::get_class(){
  return new RString("Array");
}

bool RArray::respond_to(RString *method){
  return RObject::respond_to(method);
}

void RArray::setValue(int pos, RObject *val){
  if (pos > arrayLength){
    RObject** nuevo = new RObject*[((pos+1)/10+1)*10];
    for (int i=0; i< arrayLength; i++)
      nuevo[i] = value[i];
    for (int i=arrayLength; i<pos; i++)
      nuevo[i] = new RObject();
    nuevo[pos] = val;
    arrayLength=pos+1;
  }
  value[pos] = val;
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
  if (n < arrayLength)
  	return value[n];
  else
	return new RObject();
}

RObject* RArray::operator[] (RInteger param){
  if (param.getValue() < arrayLength)
	return value[param.getValue()];
  else
	return new RObject();
}

RObject* RArray::operator[] (RInteger *param){
  return (*this)[*param];
}
