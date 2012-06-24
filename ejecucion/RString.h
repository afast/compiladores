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
    ~RString();
    RString(const char *arg);
    RString(char *arg);
    RString(std::string *arg);
    RString(RString *arg);
    RString *get_class();
    void setValue(const char * param);
    void setValue(std::string param);
    void setValue(std::string *param);
    void setValue(RString * param);
    bool respond_to(RString *method);
    bool operator== (RString param);
    bool operator== (std::string *param);
    bool operator== (const char *param);
};
#endif
