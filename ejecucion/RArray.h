#ifndef _ARRAY_H
#define _ARRAY_H

#include "RObject.h"

// Forward declaration
class RString;
class RBool;

class RArray: public RObject {
  private:
    RObject *value[];
    int arrayLenght;
    int nextSize;
  public:
    RObject *getValue();
    RInteger *size();
    RInteger *length();
    RArray();
    RArray(RArray *arg);
    RString *get_class();
    RBool *respond_to(RString *method);
    RBool operator== (RArray param);
};
#endif
