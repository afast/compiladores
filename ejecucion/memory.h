#ifndef _MEMORY_H
#define _MEMORY_H
#include <iostream>
#include <string>

class RDecimal;
class RString;
class RInteger;
class RClass;
class RBool;
class RArray;
class RVariable;
class RObject;
struct function_info_t;
void free_memory();
void new_pointer(RVariable* obj);
void new_pointer(RString* obj);
void new_pointer(RInteger* obj);
void new_pointer(RDecimal* obj);
void new_pointer(RClass* obj);
void new_pointer(RBool* obj);
void new_pointer(RArray* obj);
void new_object_pointer(RObject* obj);
void new_pointer(function_info_t* funcion);
void new_pointer(std::string* obj);
#endif
