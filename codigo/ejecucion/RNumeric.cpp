#include <cmath>

#include "RNumeric.h"
#include "RString.h"
#include "RInteger.h"
#include "RDecimal.h"

RString*  RNumeric::get_class(){
  return new RString("Numeric");
}

bool RNumeric::es_int(){
  return integer;
}
bool RNumeric::es_dec(){
  return decimal;
}

RString* RNumeric::to_s(){
  RString* s;
  if (integer)
    s= ((RInteger*)this)->to_s();
  else{
    if (decimal)
      s= ((RDecimal*)this)->to_s();
    else
      s= this->get_class();
  }
  return s;
}

double RNumeric::getDecimalValue(){
  if (integer)
    return ((RInteger*)this)->getDecimalValue();
  if (decimal)
    return ((RDecimal*)this)->getValue();
}

long int RNumeric::getIntValue(){
  return floor(this->getDecimalValue());
}

double RNumeric::mod(RNumeric *param1){
  if (this->es_int() && param1->es_int())
    return ((RInteger*)this)->getValue() % ((RInteger*)param1)->getValue();
  else {
    double p1, p2;
    p1 = this->getDecimalValue();
    p2 = param1->getDecimalValue();
    p1 -= floor(p1/p2)*p2;
    return p1;
  }
}
