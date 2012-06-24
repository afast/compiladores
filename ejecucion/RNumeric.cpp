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
