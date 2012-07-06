#include <iostream>
#include <sstream>
#include <string>

#include "RBool.h"
#include "RVariable.h"
#include "memory.h"

RVariable::RVariable(const char *arg){
  this->str = new std::string(arg);
  new_pointer(this);
  type = RVARIABLE;
}

RVariable::RVariable(char *arg){
  this->str = new std::string(arg);
  new_pointer(this);
  type = RVARIABLE;
}

RVariable::RVariable(std::string *arg){
  this->str = new std::string(*arg);
  new_pointer(this);
  type = RVARIABLE;
}

RVariable::RVariable(RString *arg){
  this->str = new std::string(*arg->getValue());
  new_pointer(this);
  type = RVARIABLE;
}

RVariable::~RVariable(){
  if (this->str != NULL)
    delete this->str;
  this->str = NULL;
}
