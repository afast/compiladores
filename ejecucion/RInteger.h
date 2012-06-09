#ifndef _RINTEGER_H
#define _RINTEGER_H

#include "RObject.h"

class RBool;
class RString;

class RInteger : public RObject {
  protected:
    long int value;
  public:
    long int getValue();
    RInteger();
    RInteger(long int integer);
    //RInteger *object_id(); use parent method
    RString* get_class();
    RBool* respond_to(RString *method);
    RBool * operator== (RInteger param);
    RBool * operator== (long int param);
};
#endif
