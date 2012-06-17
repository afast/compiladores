%{
/* fichero instrucciones.y */
#include <stdio.h>
#include "ejecucion/stack.h"
#include "ejecucion/base.h"
#include "ejecucion/RString.h"
#include "ejecucion/RInteger.h"

void yyerror(const char *s)
{
        fprintf(stderr, "error: %s\n", s);
}

extern "C"
{
        int yyparse(void);
        int yylex(void);  
        int yywrap()
        {
                return 1;
        }

}




char *str;
std::list<Instruccion*> *codigoGlobal;
void generar_puts(char *str);
void generar_suma(int op1, int op2);
%}

%union{
  char* text;
  double real;
  int entero;
}

%start program
%token T_FIN_INSTRUCCION T_DO T_PIPE T_END T_IF T_WHILE T_LLAVE_IZQ T_LLAVE_DER
%token T_RETURN T_AND T_OR T_NOT T_PAR_IZQ T_PAR_DER T_MAS T_MENOS T_NOM_CONST
%token T_ASTER T_EXPO T_BAR T_PORCENTAJE T_MENOR_IGUAL_MAYOR T_MAYOR T_MAS_IGUAL T_MENOR T_MENOS_IGUAL
%token T_DOBLE_IGUAL T_TRIPLE_IGUAL T_NOT_IGUAL T_IGUAL_NIOQUI T_NOT_NIOQUI T_NIOQUI
%token T_ELSE T_ELSIF T_CLASS T_DEF T_COMA T_PTO T_DOS_PTOS T_THEN T_INSTANCE_CLASS
%token T_CORCHETE_IZQ T_CORCHETE_DER T_NIL T_CASE STRING STRING2 SYMBOL VARNAME T_WHEN T_IDENTIF
%token T_IGUAL T_FIN_INTERROGACION T_PUTS T_LENGTH T_GETS T_NEW T_SIZE T_EACH T_OBJECT_ID T_RESPOND_TO
%token T_INSTANCE_OF T_ATTR_READER T_ATTR_WRITER T_ACCESSOR T_LOAD T_REQUIRE T_INVOCACION_METODO
%token T_BOOL T_ANTI_BAR T_NUMERAL T_MAYOR_IGUAL T_MENOR_IGUAL T_IDENTIF_GLOBAL
%token T_ATRIBUTO T_VAR_PESOS_CERO T_VAR_PESOS T_VAR_PESOS_PESOS T_INTEGER_ABS T_ATRIBUTO_ACCESOR
%token T_FLOAT_ABS T_STRING_1 T_STRING_2 T_STRING_IZQ T_STRING_DER T_COMMAND T_ESPACIOS T_ERROR
/*=========================================================================
                          OPERATOR PRECEDENCE
=========================================================================*/
%left T_MENOS T_MAS
%left T_ASTER T_BAR
%%
program : compstmt;
compstmt : stmt
         | stmt T_FIN_INSTRUCCION
         | stmt texpr
         | stmt texpr T_FIN_INSTRUCCION;
texpr : T_FIN_INSTRUCCION stmt
      | texpr T_FIN_INSTRUCCION stmt;
stmt : /* Vacio */ 
	| output
	| if
	| while
	| each
	| variable T_IGUAL value
	| variable T_MAS_IGUAL number
	| variable T_MENOS_IGUAL number
	| def
	| class
	| T_ATTR_READER args_accesores
	| T_ATTR_WRITER args_accesores
	| T_ACCESSOR args_accesores
	| T_INVOCACION_METODO
	| load
	| require;
value : T_GETS
	| T_BOOL
	| T_INSTANCE_CLASS
	| T_NEW T_PAR_IZQ args_new T_PAR_DER
	| expr_numeric
	| expr_string
	| expr_bool
	| case
	| array;
string : T_STRING_1
	| T_STRING_2
	| T_COMMAND;
output : T_PUTS value {generar_puts($<text>2);};
number : T_INTEGER_ABS {printf("%i\n", $<entero>1);}
	| T_MENOS T_INTEGER_ABS {printf("%i\n", (-1)*$<entero>2);}
	| T_MAS T_INTEGER_ABS {printf("%i\n", $<entero>1);}
	| T_FLOAT_ABS {printf("%f\n", $<real>1);}
	| T_MENOS T_FLOAT_ABS {printf("%f\n", (-1)*$<real>2);}
	| T_MAS T_FLOAT_ABS {printf("%f\n", $<real>1);};
expr_numeric : number
	| variable
	| T_OBJECT_ID
	| T_SIZE
	| T_LENGTH
	| expr_numeric T_MAS expr_numeric {generar_suma($<entero>1, $<entero>3);}
	| expr_numeric T_ASTER expr_numeric
	| expr_numeric T_MENOS expr_numeric
	| expr_numeric T_BAR expr_numeric
	| expr_numeric T_EXPO expr_numeric
	| expr_numeric T_PORCENTAJE expr_numeric
	| T_PAR_IZQ expr_numeric T_PAR_DER;
expr_string : string
	| variable
	| T_NIL
	| expr_string T_ASTER T_INTEGER_ABS
	| expr_string T_MAS expr_string
	| T_PAR_IZQ expr_string T_PAR_DER;
expr_bool : T_RESPOND_TO T_PAR_IZQ expr_string T_PAR_DER
	| T_INSTANCE_OF expr_string
	| value T_AND value
	| value T_OR value
	| T_NOT value
	| value  T_MAYOR value
	| value  T_MAYOR_IGUAL value
	| value  T_MENOR value
	| value  T_MENOR_IGUAL value
	| value  T_DOBLE_IGUAL value
	| value  T_NOT_IGUAL value
	| T_PAR_IZQ value T_PAR_DER;
variable : T_IDENTIF
	| T_ATRIBUTO
	| T_IDENTIF T_CORCHETE_IZQ T_INTEGER_ABS T_CORCHETE_DER;

if : T_IF expr_bool compstmt recursive_elsif opt_else T_END;
recursive_elsif : /* Vacio */
                | T_ELSIF expr_bool compstmt recursive_elsif;
opt_else : /* Vacio */
         | T_ELSE compstmt;
while : T_WHILE expr_bool compstmt T_END;
case : T_CASE rec_when_then T_END
	| T_CASE T_FIN_INSTRUCCION rec_when_then T_END;

rec_when_then : T_WHEN expr_bool T_THEN value T_FIN_INSTRUCCION
              | rec_when_then T_WHEN expr_bool T_THEN value T_FIN_INSTRUCCION
	      | T_WHEN expr_bool T_THEN value
              | rec_when_then T_WHEN expr_bool T_THEN value;
def :	T_DEF T_IDENTIF	argdecl compstmt T_END
	| T_DEF T_IDENTIF compstmt T_END;
argdecl : T_PAR_IZQ arglist T_PAR_DER T_FIN_INSTRUCCION
	| T_PAR_IZQ T_PAR_DER T_FIN_INSTRUCCION; /*para representar pej: funcion()*/
	| arglist T_FIN_INSTRUCCION;
arglist : T_IDENTIF arglist_recur;  /*ver lo de recursion por la izq y por la der*/
arglist_recur :	/*vacio*/
	| T_COMA T_IDENTIF arglist_recur;
array :	T_CORCHETE_IZQ list_values T_CORCHETE_DER
	| T_CORCHETE_IZQ T_CORCHETE_DER;
list_values: value
	| value T_COMA list_values;
class :	T_CLASS T_NOM_CONST compstmt T_END;
args_accesores : T_ATRIBUTO_ACCESOR args_accesores_recur;
args_accesores_recur :	/*vacio*/
	| args_accesores_recur T_COMA T_ATRIBUTO_ACCESOR;
args_new : value args_new_recur;
args_new_recur :	/*vacio*/
	| args_new_recur T_COMA	value;

load : T_LOAD expr_string_load_require;
require : T_REQUIRE expr_string_load_require;
expr_string_load_require : T_STRING_1
	| variable
	| T_NIL
	| expr_string_load_require T_ASTER T_INTEGER_ABS
	| expr_string_load_require T_MAS expr_string_load_require;
each : T_EACH T_DO T_PIPE T_IDENTIF T_PIPE compstmt T_END;

%%

main()
{

codigoGlobal = new std::list<Instruccion*>();
/*Acciones a ejecutar antes del análisis*/
yyparse();
/*Acciones a ejecutar después del análisis*/
Instruccion *fin = new Instruccion;
fin->op = FIN;
codigoGlobal->push_back(fin);
ejecutar(codigoGlobal);
}
void generar_puts(char* str){
	Instruccion* instruccion = new Instruccion;
	instruccion->op = PUTS;
	instruccion->arg1 = new RString(str);
	codigoGlobal->push_back(instruccion);
}
void generar_suma(int op1, int op2){
printf("entre aca111111111111111111");
	Instruccion* instruccion = new Instruccion;
	instruccion->op = ADD;
printf("entre aca222222222222222222");
	instruccion->arg1 = new RInteger(op1);
	instruccion->arg2 = new RInteger(op2);
printf("entre aca333333333333333333");
	codigoGlobal->push_back(instruccion);
printf("entre aca444444444444444444");
}
