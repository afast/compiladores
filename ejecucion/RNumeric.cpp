#include "RNumeric.h"
#include "RString.h"
#include "memory.h"

RString*  RNumeric::get_class(){
  RString *s = new RString("Numeric");
  new_pointer(s);
  return s;
}
