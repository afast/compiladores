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
    void setValue(double dec);
    RDecimal();
    RDecimal(double integer);
    //RDecimal *object_id(); use parent method
    double getDecimalValue();
    bool respond_to(RString *method);
    bool operator== (RDecimal param);
    bool operator== (double param);
    double operator= (RDecimal param);
    RString* get_class();
    RString* to_s();
};
#endif
