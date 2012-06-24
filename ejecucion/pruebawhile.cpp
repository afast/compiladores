#include <iostream>
#include <list>

#include "stack.h"
#include "memory.h"
#include "base.h"
#include "RString.h"
#include "RBool.h"

using namespace std;

int main(){
  list<Instruccion*> codigo;
  RBool *t = new RBool(true);
  new_pointer(t);
  RBool *f = new RBool(false);
  new_pointer(f);
  RString *s;
  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola1");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola2");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola3");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILE, f, NULL, NULL));
  s = new RString("hola31");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILEEND, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola32");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, t, NULL, NULL));
  s = new RString("hola4");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola41");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola42");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola5");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola6");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola7");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola8");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, t, NULL, NULL));
  s = new RString("hola9");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola10");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola11");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola12");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola13");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola14");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(WHILE, t, NULL, NULL));
  s = new RString("hola18");
  new_pointer(s);
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILEEND, t, NULL, NULL));
  codigo.push_back(nuevaInst(FIN, NULL, NULL, NULL));

  ejecutar(&codigo);
  return 0;
}
