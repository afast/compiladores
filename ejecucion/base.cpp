#include <sstream>

#include "base.h"
#include "RString.h"

void puts(RString *string_arg) {
  std::string *str = new std::string(string_arg->getValue()->data());
  while (str->at(str->size()-1) == '\n')
    str->erase(str->size()-1);
  std::cout << str->data() << std::endl;
  delete str;
}

void gets(RString *string_arg) {
  std::string *str = new std::string();
  if (string_arg->getValue() != NULL)
    delete string_arg->getValue();
  getline(std::cin, *str);
  str->push_back('\n'); // Ruby lee el string incluido el fin de linea
  string_arg->setValue(str);
}

RInteger *add(RInteger *arg1, RInteger *arg2) {
  std::RInteger *result = new std::RInteger(arg1->getValue() + arg2->getValue());
  if (arg1->getValue() != NULL)
    delete arg1->getValue();
  if (arg2->getValue() != NULL)
    delete arg2->getValue();
  return result;
}

long int getDir(void* p){
  long int id;
  std::stringstream s, sp;
  std::string str;
  sp << (void*)p;
  sp >> str;
  s << (void*)p;
  s >> std::hex >> id;
  std::cout << str << std::endl;
  std::cout << "check " << id << std::endl;
  return id;
}

void init(){
  //Default methods
  
}
