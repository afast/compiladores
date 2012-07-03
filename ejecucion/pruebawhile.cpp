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
  RBool *f = new RBool(false);
  RString *s;
  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola1");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola2");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola3");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILE, f, NULL, NULL));
  s = new RString("hola31");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILEEND, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola32");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, t, NULL, NULL));
  s = new RString("hola4");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola41");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  
  codigo.push_back(nuevaInst(IF, t, NULL, NULL));
  s = new RString("hola42");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola5");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola6");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola7");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola8");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, t, NULL, NULL));
  s = new RString("hola9");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola10");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(IF, f, NULL, NULL));
  s = new RString("hola11");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola12");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSIF, f, NULL, NULL));
  s = new RString("hola13");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(ELSE, NULL, NULL, NULL));
  s = new RString("hola14");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(END, NULL, NULL, NULL));

  codigo.push_back(nuevaInst(WHILE, t, NULL, NULL));
  s = new RString("hola18");
  codigo.push_back(nuevaInst(PUTS, s, NULL, NULL));
  codigo.push_back(nuevaInst(WHILEEND, t, NULL, NULL));
  codigo.push_back(nuevaInst(FIN, NULL, NULL, NULL));

  ejecutar(&codigo);
  return 0;
}
