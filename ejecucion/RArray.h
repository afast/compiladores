#ifndef _ARRAY_H
#define _ARRAY_H

#include "RObject.h"

// Forward declaration
class RString;
class RBool;

class RArray: public RObject {
  private:
    RObject **value;
    int arrayLength;
    int nextSize;
  public:
    RObject **getValue();
    RInteger *size();
    RInteger *length();
    RArray();
    ~RArray();
    RArray(RArray *arg);
    RString *get_class();
    void setValue(int pos, RObject *val);
    RString *to_s();
    bool respond_to(RString *method);
    bool operator== (RArray param);
    RObject* operator[] (RInteger param);
    RObject* operator[] (RInteger *param);
    RObject* operator[] (int param);
};
#endif
