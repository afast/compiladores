#include "base.h"

void puts(RString *string_arg) {
  std::string *str = new std::string(string_arg->cadena->data());
  while (str->at(str->size()-1) == '\n') {
    str->erase(str->size()-1);
  }
  std::cout << str->data() << std::endl;
}
