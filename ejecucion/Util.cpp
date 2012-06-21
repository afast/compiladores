#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include <sstream>

char* Util::intToString(int value){
	int n;
	char * aux = new char [20];
	n=sprintf(aux, "%d", value);
	return aux; 
}

char* Util::nueva_var()
{
  char* s = new char[10];
  static int actual=0;
  strcpy(s,"t_");
  strcpy(&(s[1]), intToString(actual));
  actual++;
  return s;
}

