#ifndef _MEMORY_H
#define _MEMORY_H
class RDecimal;
class RString;
class RInteger;
class RClass;
class RBool;
class RArray;
class RVariable;
class RObject;
void free_memory();
void new_pointer(RVariable* obj);
void new_pointer(RString* obj);
void new_pointer(RInteger* obj);
void new_pointer(RDecimal* obj);
void new_pointer(RClass* obj);
void new_pointer(RBool* obj);
void new_pointer(RArray* obj);
void new_pointer(RObject* obj);
#endif
