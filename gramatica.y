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
#include "ejecucion/RArray.h"
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

bool error_sintaxis=false;

void yyerror(const char *s)
{
        //fprintf(stderr, "Error: %s\n", s);
  	fprintf(stderr, "Error de sintaxis en linea %d - cerca de \"%s\"\n", yylineno, yytext);
    error_sintaxis=true;
}


char *str;
std::list<Instruccion*> *codigoGlobal;
Instruccion* generar_puts(node_tac* op);
node_tac* generar_oper_binario(code_ops oper, node_tac* op1, node_tac* op2);
node_tac* insert_tmp(RObject *value);
node_tac* generar_elsif(node_tac* condition, node_tac* stmt, node_tac* op_elsif);
node_tac* generar_if(node_tac* condition, node_tac* stmt, node_tac* op_elsif, node_tac* op_else);
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
%token T_ATRIBUTO T_VAR_PESOS_CERO T_VAR_PESOS T_VAR_ARGV T_VAR_PESOS_PESOS T_INTEGER_ABS T_ATRIBUTO_ACCESOR
%token T_FLOAT_ABS T_STRING_1 T_STRING_2 T_STRING_IZQ T_STRING_DER T_COMMAND T_ESPACIOS T_ERROR

%type <a> expr_numeric compstmt stmt texpr value output integer float variable string expr_string expr_bool if recursive_elsif opt_else while rec_when_then case argdecl def arglist list_values class args_accesores array list_values_arr
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
%right T_EXPO
%%
program : compstmt { /*printTree($1);*/ if (!error_sintaxis) generar($1, codigoGlobal); freeTree($1);};
compstmt : /* Vacio */ { $$ = NULL;}
         | stmt { $$ = new_compstmt($1);}
         | stmt T_FIN_INSTRUCCION {$$ = new_compstmt($1); }
         | stmt texpr {$$ = add_front_stmt_compstmt($1, $2); }
         | stmt texpr T_FIN_INSTRUCCION {$$ = add_front_stmt_compstmt($1, $2); };
texpr : T_FIN_INSTRUCCION stmt { $$ = new_compstmt($2);}
      | texpr T_FIN_INSTRUCCION stmt { $$ = add_stmt_compstmt($3, $1);};
stmt : output
	| if
	| while
	| each
	| variable T_IGUAL value { $$ = new_asgn($1, $3, yylineno); }
	| variable T_MAS_IGUAL value { $$ = new_asgn($1, new_numeric_op(op_plus, $1, $3, yylineno), yylineno); }
	| variable T_MENOS_IGUAL value { $$ = new_asgn($1, new_numeric_op(op_sub, $1, $3, yylineno), yylineno); }
	| def
	| class {std::cout << "nueva clase\n";}
	| T_ATTR_READER args_accesores { $$ = new_accesor_list(t_readers, $2, yylineno);}
	| T_ATTR_WRITER args_accesores { $$ = new_accesor_list(t_writers, $2, yylineno);}
	| T_ACCESSOR args_accesores { $$ = new_accesor_list(t_wr, $2, yylineno);}
	| T_INVOCACION_METODO { $$ = new_class_method_call($<text>1, NULL, yylineno); }
	| T_INVOCACION_METODO T_IGUAL value { $$ = new_class_attr_assign($<text>1, $3, yylineno); }
	| T_INVOCACION_METODO list_values { $$ = new_class_method_call($<text>1, $2, yylineno); }
  | T_IDENTIF { $$ = new_method_call($<text>1, NULL, yylineno); }
  | T_IDENTIF list_values { $$ = new_method_call($<text>1, $2, yylineno); }
	| bloque;
bloque: T_LLAVE_IZQ compstmt T_LLAVE_DER
	| T_DO compstmt T_END;
value : T_GETS { $$ = new_gets(yylineno); }
	| T_INSTANCE_CLASS
	| T_NEW T_PAR_IZQ list_values T_PAR_DER { $$ = new_class_new($<text>1, $3, yylineno); }
	| T_NEW { $$ = new_class_new($<text>1, NULL, yylineno);}
	| expr_numeric { $$ = $1; }
	| expr_string { $$ = $1; }
	| expr_bool { $$ = $1; }
	| variable { $$ = $1; }
	| case
	| expr_string_interpolado
	| array;
output : T_PUTS value { $$ = new_puts($2, yylineno);  }
       | T_PUTS T_INVOCACION_METODO { $$ = new_puts(new_class_method_call($<text>2, NULL, yylineno), yylineno); }
       ;
integer : T_INTEGER_ABS {$$ = new_number($<entero>1, yylineno);}
	| T_MENOS T_INTEGER_ABS { $$ = new_number((-1)*$<entero>2, yylineno); }
	| T_MAS T_INTEGER_ABS { $$ = new_number($<entero>2, yylineno); };
float: T_FLOAT_ABS { $$ = new_number($<real>1, yylineno); }
	| T_MENOS T_FLOAT_ABS { $$ = new_number((-1)*$<real>2, yylineno); }
	| T_MAS T_FLOAT_ABS { $$ = new_number($<real>2, yylineno); };
expr_numeric : integer
  	| float
	| T_OBJECT_ID { $$ = new_object_call($<text>1, yylineno); }
	| T_SIZE { $$ = new_object_call($<text>1, yylineno); }
	| T_LENGTH { $$ = new_object_call($<text>1, yylineno); }
	| expr_numeric T_MAS expr_numeric { $$ = new_numeric_op(op_plus, $1, $3, yylineno);}
	| expr_numeric T_ASTER expr_numeric { $$ = new_numeric_op(op_mul, $1, $3, yylineno);}
	| expr_numeric T_MENOS expr_numeric { $$ = new_numeric_op(op_sub, $1, $3, yylineno);}
	| expr_numeric T_BAR expr_numeric   { $$ = new_numeric_op(op_div, $1, $3, yylineno);}	
	| expr_numeric T_EXPO expr_numeric  { $$ = new_numeric_op(op_pow, $1, $3, yylineno);}
	| expr_numeric T_PORCENTAJE expr_numeric { $$ = new_numeric_op(op_mod, $1, $3, yylineno);}
	| expr_numeric T_MAS variable { $$ = new_numeric_op(op_plus, $1, $3, yylineno);}
	| expr_numeric T_ASTER variable { $$ = new_numeric_op(op_mul, $1, $3, yylineno);}
	| expr_numeric T_MENOS variable { $$ = new_numeric_op(op_sub, $1, $3, yylineno);}
	| expr_numeric T_BAR variable   { $$ = new_numeric_op(op_div, $1, $3, yylineno);}	
	| expr_numeric T_EXPO variable  { $$ = new_numeric_op(op_pow, $1, $3, yylineno);}
	| expr_numeric T_PORCENTAJE variable { $$ = new_numeric_op(op_mod, $1, $3, yylineno);}
	| variable T_MAS expr_numeric { $$ = new_numeric_op(op_plus, $1, $3, yylineno);}
	| variable T_ASTER expr_numeric { $$ = new_numeric_op(op_mul, $1, $3, yylineno);}
	| variable T_MENOS expr_numeric { $$ = new_numeric_op(op_sub, $1, $3, yylineno);}
	| variable T_BAR expr_numeric   { $$ = new_numeric_op(op_div, $1, $3, yylineno);}	
	| variable T_EXPO expr_numeric  { $$ = new_numeric_op(op_pow, $1, $3, yylineno);}
	| variable T_PORCENTAJE expr_numeric { $$ = new_numeric_op(op_mod, $1, $3, yylineno);}
	| variable T_MAS variable { $$ = new_numeric_op(op_plus, $1, $3, yylineno);}
	| variable T_ASTER variable { $$ = new_numeric_op(op_mul, $1, $3, yylineno);}
	| variable T_MENOS variable { $$ = new_numeric_op(op_sub, $1, $3, yylineno);}
	| variable T_BAR variable   { $$ = new_numeric_op(op_div, $1, $3, yylineno);}	
	| variable T_EXPO variable  { $$ = new_numeric_op(op_pow, $1, $3, yylineno);}
	| variable T_PORCENTAJE variable { $$ = new_numeric_op(op_mod, $1, $3, yylineno);}
	| T_PAR_IZQ expr_numeric T_PAR_DER{ $$ = $2; }; 
expr_string : string { $$ = $1; }
	| T_NIL { $$ = new_nil(yylineno); }
	| expr_string T_ASTER expr_numeric { $$ = new_mul_string($1, $3, yylineno);}
	| expr_string T_ASTER variable { $$ = new_mul_string($1, $3, yylineno);}
	| expr_string T_MAS expr_string { $$ = new_add_string($1, $3, yylineno); }
	| variable T_MAS expr_string { $$ = new_add_string($1, $3, yylineno); }
	| expr_string T_MAS variable { $$ = new_add_string($1, $3, yylineno); }
	| T_PAR_IZQ expr_string T_PAR_DER { $$ = $2; };
string : T_STRING_1 { $$ = new_string($<text>1, yylineno); }
	| T_STRING_2 { $$ = new_string($<text>1, yylineno); }
	| T_COMMAND { $$ = new_command($<text>1, yylineno); };
expr_bool : T_BOOL {$$ = new_boolean_op(b_is_bool, new_bool($<entero>1, yylineno), NULL, yylineno); }
  | T_RESPOND_TO T_PAR_IZQ expr_string T_PAR_DER { $$ = new_object_call($<text>1, new_arguments($3, yylineno), yylineno); }
	| T_INSTANCE_OF expr_string { $$ = new_object_call($<text>1, new_arguments($2, yylineno), yylineno); }
	/*| T_PAR_IZQ value T_PAR_DER{ $$ = new_boolean_op(b_is_bool, $2, NULL, yylineno);}*/
	| T_NOT value { $$ = new_boolean_op(b_not, $2, NULL, yylineno);}
	| value  T_MAYOR value { $$ = new_boolean_op(b_mayor, $1, $3, yylineno);}
	| value  T_MAYOR_IGUAL value { $$ = new_boolean_op(b_mayor_igual, $1, $3, yylineno);}
	| value  T_MENOR value { $$ = new_boolean_op(b_menor, $1, $3, yylineno); }
	| value  T_MENOR_IGUAL value { $$ = new_boolean_op(b_menor_igual, $1, $3, yylineno);}
	| value  T_DOBLE_IGUAL value { $$ = new_boolean_op(b_doble_igual, $1, $3, yylineno);}
	| value  T_NOT_IGUAL value { $$ = new_boolean_op(b_not_igual, $1, $3, yylineno);}
	| value T_AND value { $$ = new_boolean_op(b_and, $1, $3, yylineno);}
	| value T_OR value { $$ = new_boolean_op(b_or, $1, $3, yylineno);}
  | T_PAR_IZQ expr_bool T_PAR_DER {$$ = $2;};
variable : T_IDENTIF { $$ = new_identificador($<text>1, yylineno);}
	| T_ATRIBUTO { $$ = new_atributo($<text>1, yylineno);}
	| T_VAR_PESOS_CERO { $$ = new_identificador_global($<text>1, yylineno);}
	| T_VAR_PESOS { $$ = new_identificador_global($<text>1, yylineno);}
	| T_VAR_PESOS_PESOS { $$ = new_identificador_global($<text>1, yylineno);}
	| T_VAR_ARGV { $$ = new_identificador_global($<text>1, yylineno);}
	| T_IDENTIF_GLOBAL { $$ = new_identificador_global($<text>1, yylineno);}
	| T_IDENTIF T_CORCHETE_IZQ value T_CORCHETE_DER { $$ = new_array_pos($<text>1, $3, yylineno);}
	| T_VAR_ARGV T_CORCHETE_IZQ value T_CORCHETE_DER {  $$ = new_array_pos($<text>1, $3, yylineno);};

if : T_IF expr_bool T_FIN_INSTRUCCION compstmt recursive_elsif opt_else T_END { $$ = new_if($2, $4, $5, $6, yylineno);  };
recursive_elsif : /* Vacio */ { $$ = NULL; }
                | recursive_elsif T_ELSIF expr_bool T_FIN_INSTRUCCION compstmt { $$ = new_elsif($3, $5, $1, yylineno); };
opt_else : /* Vacio */ { $$ = NULL; }
         | T_ELSE T_FIN_INSTRUCCION compstmt { $$ = $3; };
case : T_CASE T_WHEN expr_bool T_THEN value T_FIN_INSTRUCCION rec_when_then T_END { $$ = new_case($3, $5, $7); }
	| T_CASE T_FIN_INSTRUCCION T_WHEN expr_bool T_THEN value T_FIN_INSTRUCCION rec_when_then T_END { $$ = new_case($4, $6, $8); }; 
rec_when_then : /* Vacio */ { $$ = NULL; }
                | rec_when_then T_WHEN expr_bool T_THEN value T_FIN_INSTRUCCION { $$ = new_when_rec($3, $5, $1); };

while : T_WHILE expr_bool T_FIN_INSTRUCCION compstmt T_END { $$ = new_while($2, $4, yylineno); };
def :	T_DEF T_IDENTIF argdecl T_FIN_INSTRUCCION compstmt T_END { $$ = new_method($<text>2, $3, $5,yylineno);}
	| T_DEF T_IDENTIF T_FIN_INSTRUCCION compstmt T_END { $$ = new_method($<text>2, NULL, $4, yylineno);};
argdecl : T_PAR_IZQ arglist T_PAR_DER
	| T_PAR_IZQ T_PAR_DER /*para representar pej: funcion()*/
	| arglist;
arglist :	T_IDENTIF { $$ = new_arguments(new_identificador($<text>1, yylineno), yylineno);}
	| arglist T_COMA T_IDENTIF { $$ = add_argument(new_identificador($<text>3, yylineno), $1, yylineno);};
array :	T_CORCHETE_IZQ value T_COMA list_values_arr T_CORCHETE_DER { $$ = new_array($2, $4, yylineno);}
  | T_CORCHETE_IZQ value T_CORCHETE_DER { $$ = new_array($2, yylineno);}
	| T_CORCHETE_IZQ T_CORCHETE_DER { $$ = new_array(yylineno);};
list_values_arr: value { $$ = new_array($1, yylineno);} 
	| list_values_arr T_COMA value { $$ = add_elem($1, $3, yylineno);};
list_values: value { $$ = new_params($1, yylineno);}
	| list_values T_COMA value { $$ = add_param($1, $3, yylineno);};
class :	T_CLASS T_NOM_CONST T_FIN_INSTRUCCION compstmt T_END { $$ = new_class($<text>2, $4, yylineno);};
args_accesores : T_ATRIBUTO_ACCESOR { $$ = new_accesores($<text>1, yylineno);}
               | args_accesores T_COMA T_ATRIBUTO_ACCESOR { $$ = new_accesores($<text>2, $1, yylineno);};
each : T_EACH T_DO T_PIPE T_IDENTIF T_PIPE compstmt T_END;
expr_string_interpolado : T_STRING_IZQ expr_string_interpolado_recur T_STRING_DER;
expr_string_interpolado_recur : /*vacio*/
	| value
	| expr_string_interpolado_recur T_STRING_CENTER value;


%%

main( int argc, char *argv[] )
{ 
	if(argc > 1){
		extern FILE *yyin;
		++argv;
		--argc;
		yyin = fopen( argv[0], "r" );
		
		set_global_variable(new std::string("$0"), new RString(argv[0]));
		set_global_variable(new std::string("$$"), new RInteger(getpid()));
		set_global_variable(new std::string("$:"), new RString("."));

		int i = 1;
		RArray *myArgv = new RArray();
		while(i < argc){
			myArgv->setValue(i - 1, new RString(argv[i])); 
			i++;
		}
		set_global_variable(new std::string("ARGV"), myArgv);
		codigoGlobal = new std::list<Instruccion*>();
		initializer();
		yyparse();
    if (!error_sintaxis){
      Instruccion *fin = new Instruccion;
      fin->op = FIN;
      fin->arg1 = NULL;
      fin->arg3 = NULL;
      fin->arg2 = NULL;
      codigoGlobal->push_back(fin);
//      printCodigo();
      ejecutar(codigoGlobal);
    }
	} else {
		std::cout << "No se indica archivo para ejecutar. La ejecucion debe usar el formato:" << std::endl;
		std::cout << "       myruby archivo.rb arg1 arg2 arg3 ... argN" << std::endl;
	}

}

void printCodigo() {
  std::cout << "=========================================" << std::endl; 
  std::list<Instruccion *>::iterator it = codigoGlobal->begin();
  Instruccion *ri;
  do {
    ri = *it++;
    switch (ri->op) {
      case FIN   : std::cout << "FIN" << std::endl; break;
      case PUTS  : std::cout << "PUTS " << *ri->arg1->to_s()->getValue() << std::endl; break;
      case ADD   : std::cout << "ADD " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue() << std::endl; break;
      case SUB   : std::cout << "SUB " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue() << std::endl; break;
      //case MULT   : std::cout << "MULT " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue() << std::endl; break;
      //case ASGN   : std::cout << "ASGN " << *ri->arg1->to_s()->getValue() << (ri->arg2->to_s()->getValue() != NULL ? *ri->arg2->to_s()->getValue() : "uninitialized") << std::endl; break;
      case IF   : std::cout << "IF "  << std::endl; break;
      case ELSE   : std::cout << "ELSE "  << std::endl; break;
      case ELSIF   : std::cout << "ELSIF "  << std::endl; break;
      case ELSIFCOND   : std::cout << "ELSIFCOND "  << std::endl; break;
      case END   : std::cout << "END "  << std::endl; break;
      case CASE   : std::cout << "CASE "  << std::endl; break;
      case CASEREC   : std::cout << "CASEREC "  << std::endl; break;
      case CASERECCOND   : std::cout << "CASERECCOND "  << std::endl; break;
      case WHILE : std::cout << "WHILE "  << std::endl; break;
      case WHILEEND : std::cout << "WHILEEND "  << std::endl; break;
      case NOT : std::cout << "NOT " << *ri->arg2->to_s()->getValue()  << std::endl; break;
      case G : std::cout << "G " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case GE : std::cout << "GE " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case L  : std::cout << "L " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case LE : std::cout << "LE " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case EQ : std::cout << "EQ " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case NEQ : std::cout << "NEQ " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case TOBOOL : std::cout << "TOBOOL " << *ri->arg2->to_s()->getValue()  << std::endl; break;
      case AND : std::cout << "AND " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case OR : std::cout << "OR " << *ri->arg2->to_s()->getValue() << *ri->arg3->to_s()->getValue()  << std::endl; break;
      case PUT_INST_V : std::cout << "PUT_INST_V" << std::endl; break;
      case GET_INST_V : std::cout << "GET_INST_V" << std::endl; break;
      case PUTV : std::cout << "PUTV" << std::endl; break;
      case PUSH_ARG: std::cout << "PUSH_ARG" << std::endl; break;
      case POP_ARG: std::cout << "POP_ARG" << std::endl; break;
      case CALL: std::cout << "CALL" << std::endl; break;
      case CLASS_INST_CALL: std::cout << "CLASS_INST_CALL" << std::endl; break;
      case NEW: std::cout << "NEW" << std::endl; break;
      case ENDFUNC: std::cout << "ENDFUNC" << std::endl; break;
      case RETURN: std::cout << "RETURN" << std::endl; break;
      case ASGN: std::cout << "ASGN" << std::endl; break;
      default: std::cout << "hay una op no reconocida" <<  std::endl;
        break;
    }
  } while (ri->op != FIN);
  std::cout << "=========================================" << std::endl; 
}

