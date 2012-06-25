#ifndef _BOOL_H
#define _BOOL_H
#include "RObject.h"

// Forward declaration
class RString;

class RBool: public RObject {
  protected:
    bool value;
  public:
    bool getValue();
    void setValue(bool val);
    RBool();
    RBool(bool arg);
    RBool(RBool *arg);
    RString *get_class();
    RString *to_s();
    bool respond_to(RString *method);
    bool operator= (RBool param);
    bool operator== (RBool param);
    bool operator|| (RBool param);
    bool operator&& (RBool param);
};
#endif
