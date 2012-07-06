#ifndef _RNUMERIC_H
#define _RNUMERIC_H

#include "RObject.h"

class RBool;
class RString;

class RNumeric : public RObject {
  protected:
    bool integer, decimal;
  public:
    RString* get_class();
    virtual RString* to_s();
    virtual double getDecimalValue();
    long int getIntValue();
    bool es_int();
    bool es_dec();
    double mod(RNumeric *param1);
};
#endif
