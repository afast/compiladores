#ifndef _RCLASS_H
#define _RCLASS_H

#include <iostream>
#include <list>
#include <unordered_map>

#include "RObject.h"
#include "stack.h"

class RBool;
class RString;

class RClass : public RObject {
  private:
    RString* name;
    std::list<RString*> method_names;
    std::unordered_map<std::string, RObject*> instance_variables;
    std::unordered_map<std::string, std::list<Instruccion*>*> methods;
    void init(RString* param);
  public:
    RClass(const char* param);
    RClass(std::string* param);
    RClass(RString* param);
    ~RClass();
    RString* get_class();
    RString* to_s();
    bool respond_to(RString *method);
    void add_method(std::string* method, std::list<Instruccion*> *codigo);
    void add_method(RString* method, std::list<Instruccion*> *codigo);
    void add_instance_variable(RString* variable);
    void add_instance_variable(std::string* variable);
    RClass* get_instance();
};
#endif
