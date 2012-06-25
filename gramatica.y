%{
/* fichero instrucciones.y */
#include <stdio.h>
#include <string.h>
#include "ejecucion/stack.h"
#include "ejecucion/base.h"
#include "ejecucion/RString.h"
#include "ejecucion/RInteger.h"
#include "ejecucion/Util.h"
#include "ejecucion/RBool.h"
#include "ast.h"
#include "generador.h"

extern "C"
{
        int yyparse(void);
        int yylex(void);
        int yywrap()
        {
                return 1;
        }

}

extern char* yytext;
extern int yylineno;

void yyerror(const char *s)
{
        //fprintf(stderr, "Error: %s\n", s);
  	printf("Error (FALTA TIPO DE ERROR) en linea %d - cerca de \"%s\"\n", yylineno, yytext);

}


char *str;
std::list<Instruccion*> *codigoGlobal;
Instruccion* generar_puts(node_tac* op);
node_tac* generar_oper_binario(code_ops oper, node_tac* op1, node_tac* op2);
node_tac* insert_tmp(RObject *value);
node_tac* generar_elsif(node_tac* condition, node_tac* stmt, node_tac* op_elsif);
//node_tac* generar_if(node_tac* condition, node_tac* stmt, node_tac* op_elsif, node_tac* op_else);
node_tac* generar_if_sigue(node_tac* result, node_tac* stmt, node_tac* op_elsif, node_tac* op_else);
node_tac* generar_if(node_tac* condition);
node_tac* generar_else(node_tac* stmt);
void printCodigo();


%}

%union{
  char* text;
  double real;
  long int entero;
  ast* a;
}

%start program
%token T_FIN_INSTRUCCION T_DO T_PIPE T_END T_IF T_WHILE T_LLAVE_IZQ T_LLAVE_DER
%token T_RETURN T_AND T_OR T_NOT T_PAR_IZQ T_PAR_DER T_MAS T_MENOS T_NOM_CONST T_STRING_CENTER
%token T_ASTER T_EXPO T_BAR T_PORCENTAJE T_MENOR_IGUAL_MAYOR T_MAYOR T_MAS_IGUAL T_MENOR T_MENOS_IGUAL
%token T_DOBLE_IGUAL T_TRIPLE_IGUAL T_NOT_IGUAL T_IGUAL_NIOQUI T_NOT_NIOQUI T_NIOQUI
%token T_ELSE T_ELSIF T_CLASS T_DEF T_COMA T_PTO T_DOS_PTOS T_THEN T_INSTANCE_CLASS
%token T_CORCHETE_IZQ T_CORCHETE_DER T_NIL T_CASE STRING STRING2 SYMBOL VARNAME T_WHEN T_IDENTIF
%token T_IGUAL T_FIN_INTERROGACION T_PUTS T_LENGTH T_GETS T_NEW T_SIZE T_EACH T_OBJECT_ID T_RESPOND_TO
%token T_INSTANCE_OF T_ATTR_READER T_ATTR_WRITER T_ACCESSOR T_LOAD T_REQUIRE T_INVOCACION_METODO
%token T_BOOL T_ANTI_BAR T_NUMERAL T_MAYOR_IGUAL T_MENOR_IGUAL T_IDENTIF_GLOBAL
%token T_ATRIBUTO T_VAR_PESOS_CERO T_VAR_PESOS T_VAR_PESOS_PESOS T_INTEGER_ABS T_ATRIBUTO_ACCESOR
%token T_FLOAT_ABS T_STRING_1 T_STRING_2 T_STRING_IZQ T_STRING_DER T_COMMAND T_ESPACIOS T_ERROR

%type <a> expr_numeric compstmt stmt texpr value output number variable string expr_string expr_bool if recursive_elsif opt_else
/*=========================================================================
                          OPERATOR PRECEDENCE
=========================================================================*/
%left T_OR
%left T_AND
%left T_DOBLE_IGUAL T_NOT_IGUAL
%left T_MAYOR T_MAYOR_IGUAL T_MENOR T_MENOR_IGUAL
%left T_MENOS T_MAS
%left T_ASTER T_BAR T_PORCENTAJE
%left T_NOT
%left T_EXPO
%%
program : compstmt { printTree($1); generar($1, codigoGlobal); freeTree($1);};
compstmt : stmt { $$ = new_compstmt($1);}
         | stmt T_FIN_INSTRUCCION {$$ = new_compstmt($1);}
         | stmt texpr {$$ = add_front_stmt_compstmt($1, $2);}
         | stmt texpr T_FIN_INSTRUCCION {$$ = add_front_stmt_compstmt($1, $2);};
texpr : T_FIN_INSTRUCCION stmt { $$ = new_compstmt($2);}
      | texpr T_FIN_INSTRUCCION stmt { $$ = add_stmt_compstmt($3, $1);};
stmt : /* Vacio */ { $$ = NULL; }
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
value : T_GETS { $$ = new_gets(); }
	| T_BOOL {$$ = new_bool($<entero>1);}
	| T_INSTANCE_CLASS
	| T_NEW T_PAR_IZQ args_new T_PAR_DER
	| expr_numeric { $$ = $1; }
	| expr_string { $$ = $1; }
	| expr_bool { $$ = $1; }
	| case
	| expr_string_interpolado
	| array;
string : T_STRING_1 { $$ = new_string($<text>1); }
	| T_STRING_2 { $$ = new_string($<text>1); }
	| T_COMMAND { $$ = new_command($<text>1); }
output : T_PUTS value { $$ = new_puts($2); }
number : T_INTEGER_ABS {$$ = new_number($<entero>1);}
	| T_MENOS T_INTEGER_ABS { $$ = new_number((-1)*$<entero>2); }
	| T_MAS T_INTEGER_ABS { $$ = new_number($<entero>2); }
	| T_FLOAT_ABS { $$ = new_number($<real>1); }
	| T_MENOS T_FLOAT_ABS { $$ = new_number((-1)*$<real>2); }
	| T_MAS T_FLOAT_ABS { $$ = new_number($<real>2); };
expr_numeric : number { $$ = $1; }
	| variable { $$ = $1; }
	| T_OBJECT_ID { $$ = new_object_call($<text>1); }
	| T_SIZE { $$ = new_object_call($<text>1); }
	| T_LENGTH { $$ = new_object_call($<text>1); }
	| expr_numeric T_MAS expr_numeric { $$ = new_numeric_op(op_plus, $1, $3);}
	| expr_numeric T_ASTER expr_numeric { $$ = new_numeric_op(op_mul, $1, $3);}
	| expr_numeric T_MENOS expr_numeric { $$ = new_numeric_op(op_sub, $1, $3);}
	| expr_numeric T_BAR expr_numeric   { $$ = new_numeric_op(op_div, $1, $3);}	
	| expr_numeric T_EXPO expr_numeric  { $$ = new_numeric_op(op_pow, $1, $3);}
	| expr_numeric T_PORCENTAJE expr_numeric { $$ = new_numeric_op(op_mod, $1, $3);}
	| T_PAR_IZQ expr_numeric T_PAR_DER{ $$ = $2; }; 
expr_string : string { $$ = $1; }
	| variable { $$ = $1; }
	| T_NIL { $$ = new_nil(); }
	| expr_string T_ASTER T_INTEGER_ABS { $$ = new_mul_string($1, $<entero>3);}
	| expr_string T_MAS expr_string { $$ = new_add_string($1, $3); }
	| T_PAR_IZQ expr_string T_PAR_DER { $$ = $2; };
expr_bool : T_RESPOND_TO T_PAR_IZQ expr_string T_PAR_DER { $$ = new_object_call($<text>1, new_arguments($3)); }
	| T_INSTANCE_OF expr_string { $$ = new_object_call($<text>1, new_arguments($2)); }
	| T_PAR_IZQ value T_PAR_DER{ std::cout << "PAR BOOL" << std::endl; $$ = new_boolean_op(b_is_bool, $2, NULL);}
	| T_NOT value { $$ = new_boolean_op(b_not, $2, NULL);}
	| value  T_MAYOR value { $$ = new_boolean_op(b_mayor, $1, $3);}
	| value  T_MAYOR_IGUAL value { $$ = new_boolean_op(b_mayor_igual, $1, $3);}
	| value  T_MENOR value { $$ = new_boolean_op(b_menor, $1, $3);}
	| value  T_MENOR_IGUAL value { $$ = new_boolean_op(b_menor_igual, $1, $3);}
	| value  T_DOBLE_IGUAL value { $$ = new_boolean_op(b_doble_igual, $1, $3);}
	| value  T_NOT_IGUAL value { $$ = new_boolean_op(b_not_igual, $1, $3);}
	| value T_AND value { std::cout << "T_AND" << std::endl; $$ = new_boolean_op(b_and, $1, $3);}
	| value T_OR value { $$ = new_boolean_op(b_or, $1, $3);};
variable : T_IDENTIF { $$ = new_identificador($<text>1);}
	| T_ATRIBUTO { $$ = new_atributo($<text>1);}
	| T_IDENTIF T_CORCHETE_IZQ T_INTEGER_ABS T_CORCHETE_DER { $$ = new_array_pos($<text>1, $<entero>3);};

if : T_IF expr_bool compstmt recursive_elsif opt_else T_END { $$ = new_if($2, $3, $4, $5); }
recursive_elsif : /* Vacio */ { $$ = NULL; }
                | T_ELSIF expr_bool compstmt recursive_elsif { $$ = new_elsif($2, $3, $4); };
opt_else : /* Vacio */ { $$ = NULL; }
         | T_ELSE compstmt { $$ = $2; };
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
expr_string_interpolado : T_STRING_IZQ expr_string_interpolado_recur T_STRING_DER;
expr_string_interpolado_recur : /*vacio*/
	| value
	| expr_string_interpolado_recur T_STRING_CENTER value;


%%

main()
{

  codigoGlobal = new std::list<Instruccion*>();
  initializer();
  /*Acciones a ejecutar antes del análisis*/
  yyparse();
  /*Acciones a ejecutar después del análisis*/
  /* Indicar final del programa */
  Instruccion *fin = new Instruccion;
  fin->op = FIN;
  codigoGlobal->push_back(fin);
  printCodigo();
  ejecutar(codigoGlobal);
}

void printCodigo() {
  std::cout << "=========================================" << std::endl; 
  std::list<Instruccion *>::iterator it = codigoGlobal->begin();
  Instruccion *ri;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : std::cout << "FIN" << std::endl; break;
      case PUTS  : std::cout << "PUTS " << std::endl; break;
      case ADD   : std::cout << "ADD " << std::endl; break;
      case MULT   : std::cout << "MULT " << std::endl; break;
      case IF   : std::cout << "IF "  << std::endl; break;
      case ELSE   : std::cout << "ELSE "  << std::endl; break;
      case ELSIF   : std::cout << "ELSIF "  << std::endl; break;
      case ELSIFCOND   : std::cout << "ELSIFCOND "  << std::endl; break;
      case END   : std::cout << "END "  << std::endl; break;
      case WHILE : std::cout << "WHILE "  << std::endl; break;
      case WHILEEND : std::cout << "WHILEEND "  << std::endl; break;
      case NOT : std::cout << "NOT "  << std::endl; break;
      case G : std::cout << "G "  << std::endl; break;
      case GE : std::cout << "GE "  << std::endl; break;
      case L  : std::cout << "L "  << std::endl; break;
      case LE : std::cout << "LE "  << std::endl; break;
      case EQ : std::cout << "EQ "  << std::endl; break;
      case NEQ : std::cout << "NEQ "  << std::endl; break;
      case TOBOOL : std::cout << "TOBOOL "  << std::endl; break;
      case AND : std::cout << "AND "  << std::endl; break;
      case OR : std::cout << "OR "  << std::endl; break;
      default: break;
    }
  } while (ri->op != FIN);
}

