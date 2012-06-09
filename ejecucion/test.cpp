#include <iostream>
#include <list>
#include "base.h"
#include "stack.h"

std::list<Instruccion*> *codigo;
int ip=0; // instruction pointer

int main()  {
  codigo = new std::list<Instruccion*>;
  Instruccion *i0, *i1, *i2, *i3;
  std::string *test = new std::string("hola\na todos\n\n");
  RObject o1, o2;
  RString s1;
  RInteger int1;
  o2.dir = &int1;
  o1.dir = &s1;
  i0 = new Instruccion;
  i1 = new Instruccion;
  i2 = new Instruccion;
  i3 = new Instruccion;
  i0->op = GETS;
  i0->arg1 = &o1;
  s1.cadena = test;
  i1->op = PUTS;
  i2->op = FIN;
  i1->arg1 = &o1;
  i3->op = OBJID;
  i3->arg1 = &o2;
  i3->arg2 = &o1;
  codigo->push_back(i0);
  codigo->push_back(i1);
  codigo->push_back(i3);
  codigo->push_back(i2);
  ejecutar(codigo);
  delete s1.cadena;
  for (std::list<Instruccion*>::iterator it = codigo->begin(); it != codigo->end(); it++)
    delete *it;
  delete codigo;
  return 0;
}
