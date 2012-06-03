#include "base.h"
#include "stack.h"

struct instruccion codigo[999];
int ip=0; // instruction pointer

int main()  {
  std::string *test = new std::string("hola\na todos\n\n");
  RString s1;
  s1.cadena = test;
  struct instruccion i0;
  struct instruccion i1;
  struct instruccion i2;
  i0.op = GETS;
  i0.arg1 = &s1;
  i1.op = PUTS;
  i2.op = FIN;
  i1.arg1 = &s1;
  codigo[0] = i0;
  codigo[1] = i1;
  codigo[2] = i2;
  ejecutar(codigo);
  return 0;
}
