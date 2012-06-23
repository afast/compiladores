#ifndef _MEMORY_H
#define _MEMORY_H
class RString;
class RInteger;
class RClass;
class RBool;
class RArray;
void free_memory();
void new_pointer(RString* obj);
void new_pointer(RInteger* obj);
void new_pointer(RClass* obj);
void new_pointer(RBool* obj);
void new_pointer(RArray* obj);
#endif
