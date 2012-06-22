#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "RObject.h"

enum obj_type { RSTRING, TOBJECT, RINT, RCLASS, RARRAY, RNIL };

void puts(RString *string_arg);
void gets(RString *string_arg);
void assign_tmp(RString *name, RObject * value);
void add(RString *arg1, RString *arg2, RString *arg3);
void mult(RString *arg1, RString *arg2, RString *arg3);
void sub(RString *arg1, RString *arg2, RString *arg3);
void div(RString *arg1, RString *arg2, RString *arg3);
void pow(RString *arg1, RString *arg2, RString *arg3);
void mod(RString *arg1, RString *arg2, RString *arg3);
void init();
long int getDir(void* p);
#endif
