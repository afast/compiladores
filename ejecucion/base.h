#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include "RObject.h"

enum obj_type { RSTRING, TOBJECT, RINT, RCLASS, RARRAY, RNIL };

void puts(RString *string_arg);
void gets(RString *string_arg);
void init();
long int getDir(void* p);
#endif
