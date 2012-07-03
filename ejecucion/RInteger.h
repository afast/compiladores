#ifndef _RINTEGER_H
#define _RINTEGER_H

#include "RNumeric.h"

class RBool;
class RString;

class RInteger : public RNumeric {
  protected:
    long int value;
  public:
    long int getValue();
    RInteger();
    RInteger(long int integer);
    void setValue(long int val);
    //RInteger *object_id(); use parent method
    double getDecimalValue();
    bool respond_to(RString *method);
    bool operator== (RInteger param);
    bool operator== (long int param);
    long int operator= (RInteger param);
    RString* to_s();
    RString* get_class();
};
#endif
