#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <unordered_map>

class RString;
class RCommand;
class RObject;
class RBool;


void puts(RString *string_arg);
void puts(RCommand *command);
void gets(RString *string_arg);
void init();
long int getDir(void* p);
RBool* mayor(RObject* arg1, RObject* arg2);
RBool* mayor_igual(RObject* arg1, RObject* arg);
RBool* menor(RObject* arg1, RObject* arg);
RBool* menor_igual(RObject* arg1, RObject* arg);
RBool* igual(RObject* arg1, RObject* arg);
bool extraer_bool(RObject* arg);
void error_generando(const char * msj);
#endif
