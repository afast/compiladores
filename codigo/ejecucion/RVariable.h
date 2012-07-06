#ifndef _RVARIABLE_H
#define _RVARIABLE_H

#include <iostream>
#include <string>

#include "RString.h"

class RVariable: public RString {
  public:
    ~RVariable();
    RVariable(const char *arg);
    RVariable(char *arg);
    RVariable(std::string *arg);
    RVariable(RString *arg);
};
#endif
