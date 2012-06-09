#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <unordered_map>

enum obj_type { RSTRING, TOBJECT, RINT, RCLASS, RARRAY, RNIL };

struct RObject {
  void *dir;
  obj_type type;
};

typedef RObject RObject;

struct RString {
  std::string *cadena;
};

struct RInteger {
  long int value;
};

typedef RString RString;
typedef RInteger RInteger;

void puts(RString *string_arg);
void gets(RString *string_arg);
void init();
long int getDir(void* p);
#endif
