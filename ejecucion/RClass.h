#ifndef _RCLASS_H
#define _RCLASS_H

#include <iostream>
#include <list>
#include <set>
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
    std::unordered_map<std::string, function_info*> methods;
    std::set<std::string*> writers;
    void init(RString* param);
  public:
    RClass(const char* param);
    RClass(std::string* param);
    RClass(RString* param);
    ~RClass();
    RString* get_class();
    RString* to_s();
    bool respond_to(RString *method);
    void add_method(std::string* method, function_info* codigo);
    void add_method(RString* method, function_info* codigo);
    void add_instance_variable(RString* variable);
    void add_instance_variable(std::string* variable);
    RClass* get_instance();
    function_info* get_function_info(RString* method);
    void set_instance_variable(RString* variable, RObject* value);
    void set_instance_variable(const char* variable, RObject* value);
    RObject* get_instance_variable(RString* variable);
    RObject* get_instance_variable(const char* variable);
    void add_accessor(RString* accesor);
    void add_writer(RString* accesor);
    void add_reader(RString* accesor);
};
#endif
