#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>

struct RObject {
  char *dir;
};

struct TRString {
  std::string *cadena;
};

typedef TRString RString;

void puts(RString *string);
#endif
