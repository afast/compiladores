#include "RArray.h"

RArray::RArray(){
  nextSize = 20;
  value = new RObject*[10];
  arrayLength = 0;
}

RArray::RArray(RArray *arg){
  nextSize = (arg->size()->getValue() % 10)*10 + 10;
  value = new RObject[nextSize];
  nextSizea += 10;
  arrayLength = arg->size();
  for (int i=0; i<arrayLength; i++)
    value[i] = *arg[i];
}

RObject **RArray::getValue(){
  return value;
}

RInteger *RArray::size(){
  return new Integer(arrayLength);
}

RInteger *RArray::length(){
  return new Integer(arrayLength);
}

RString *RArray::get_class(){
  return new RString("Array");
}

RBool *RArray::respond_to(RString *method){
  return RObject::respont_to(method);
}

RBool *RArray::operator== (RArray param){
  RBool *res;
  if (param.size() != this->size())
    res = new RBool(false);
  else if (param.size() == 0)
    res = new RBool(true);
  else {
    int i=0;
    res = new RBool(false);
    while (i < param.size() && !res->getValue()) {
      RObject object1, object2;
      object1 = *(param[i]);
      object2 = *(value[i]);
      if (object1.get_class() == object2.get_class() && object1 == object2)
        res = true;
    }
  }
  return res;
}
