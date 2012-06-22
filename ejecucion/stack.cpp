#include <iostream>
#include <string>
#include <list>

#include "stack.h"
#include "base.h"
#include "RInteger.h"
#include "RString.h"

class RString;

std::unordered_map<std::string, RObject*> tsimbolos;
std::unordered_map<std::string, std::list<Instruccion*> *> functions;
//std::unordered_map<std::string, RObject*> vTemporales;

std::unordered_map<std::string, RObject*> gobal_variables; // las variables deben agregarse a este hash variables["nombre"] = RObject*
std::unordered_map<std::string, std::list<Instruccion*>*> gobal_methods; // los metodos globales se guardan aqui methods["nombre"] = std::list<Instruccion *>*


//RObject *getValue(std::string* key){
//	return vTemporales[*key];
//}

void inicializer(){
//vTemporales = new std::unordered_map<std::string, RObject*>();
}

void ejecutar(std::list<Instruccion*> *codigo) {
  std::list<Instruccion *>::iterator it = codigo->begin();
  Instruccion *ri;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : std::cout << "Fin ejecución" << std::endl; break;
      case PUTS  : puts((RString *)ri->arg1); break;
      case GETS  : gets((RString *)ri->arg1); break;
      case ADD   : std::cout << "adddddddddddd" << std::endl;
			add((RString *)ri->arg1, (RString *)ri->arg2, (RString *)ri->arg3); 
			//std::cout << "Voy a ejecutar el ADD" << std::endl;
			//vTemporales[*(((RString *)ri->arg3)->getValue())] = add((RInteger *)ri->arg1, (RInteger *)ri->arg2); 
			//std::cout << "El valor es ----    " << vTemporales[*(((RString *)ri->arg3)->getValue())]  << std::endl;
			break;
      case OBJID : if (ri->arg1 != NULL) *((RInteger*)ri->arg1) = getDir(ri->arg2); break;
      case ASSIGN_TMP : assign_tmp((RString *)ri->arg1, ri->arg2); break;
      case MULT : mult((RString *)ri->arg1, (RString *)ri->arg2, (RString *)ri->arg3); break;
      case SUB : sub((RString *)ri->arg1, (RString *)ri->arg2, (RString *)ri->arg3); break;
    }
  } while (ri->op != FIN);
}
