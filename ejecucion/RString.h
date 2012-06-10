#ifndef _RSTRING_H
#define _RSTRING_H

#include <iostream>
#include <string>

#include "RObject.h"

class RBool;
class RString;

class RString: public RObject {
  protected:
    std::string *str;
  public:
    std::string *getValue();
    RString();
    RString(const char *arg);
    RString(char *arg);
    RString(std::string *arg);
    RString(RString *arg);
    //RInteger *object_id(); use parent method
    RString *get_class();
    RBool *respond_to(RString *method);
    RBool * operator== (RString param);
    RBool * operator== (std::string *param);
    RBool * operator== (const char *param);
    //bool operator== (RString param);
    //bool operator== (std::string *param);
    //bool operator== (const char *param);
};
#endif
