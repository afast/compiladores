#include "base.h"

void puts(RString *string_arg) {
  std::string *str = new std::string(string_arg->cadena->data());
  while (str->at(str->size()-1) == '\n') {
    str->erase(str->size()-1);
  }
  std::cout << str->data() << std::endl;
  delete str;
}

void gets(RString *string_arg){
  std::string *str = new std::string();
  if (string_arg->cadena != NULL)
    delete string_arg->cadena;
  getline(std::cin, *str);
  if (str->at(str->size()-1) == '\n')
    std::cout << "Tiene \\n al final" << std::endl;
  string_arg->cadena = str;
}
