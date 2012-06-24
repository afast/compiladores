#ifndef _RDECIMAL_H
#define _RDECIMAL_H

#include "RNumeric.h"

class RBool;
class RString;

class RDecimal : public RNumeric {
  protected:
    double value;
  public:
    double getValue();
    RDecimal();
    RDecimal(double integer);
    //RDecimal *object_id(); use parent method
    RString* get_class();
    bool respond_to(RString *method);
    bool operator== (RDecimal param);
    bool operator== (double param);
    double operator= (RDecimal param);
    RString* to_s();
};
#endif
