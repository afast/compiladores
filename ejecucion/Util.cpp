#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include <sstream>

char* Util::intToString(int value){

char* result;
if(value < 10){
  result = strdup("menor a 10");
}
else{
result = strdup("mayor o igual a 10");
}
  return result;
}

