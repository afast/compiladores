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
    bool respond_to(RString *method);
    bool operator== (RInteger param);
    bool operator== (long int param);
    long int operator= (RInteger param);
};
#endif
