%{
/* fichero instrucciones.y */
#include <stdio.h>
%}
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
output : T_PUTS value;
number : T_INTEGER_ABS
	| T_MENOS T_INTEGER_ABS
	| T_MAS T_INTEGER_ABS
	| T_FLOAT_ABS
	| T_MENOS T_FLOAT_ABS
	| T_MAS T_FLOAT_ABS;
expr_numeric : number
	| variable
	| T_OBJECT_ID
	| expr_numeric T_MAS expr_numeric
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


/*
def_blockvar :T_PIPE block_var T_PIPE;
opt_blockvar : 
             | def_blockvar;
opt_block : 
         | T_DO opt_blockvar compstmt T_END;
stmt : call T_DO opt_blockvar compstmt T_END
| stmt T_IF expr
| stmt T_WHILE expr
| lhs T_IGUAL command opt_block
| expr;
expr : mlhs T_IGUAL mrhs
    | T_RETURN call_args
    | expr T_AND expr
    | expr T_OR expr
    | T_NOT expr
    | command
    | T_NOT command
    | arg;
call : function
    | command
;
command : operation call_args
 | primary T_PTO operation call_args;
paren_or_call_args : T_PAR_IZQ T_PAR_DER
              | T_PAR_IZQ call_args T_PAR_DER;
function : operation
         | operation paren_or_call_args
         | primary T_PTO operation
         | primary T_PTO operation paren_or_call_args
arg : lhs T_IGUAL arg
| lhs T_IGUAL arg
| arg T_MAS arg | arg T_MENOS arg | arg T_ASTER arg | arg T_BAR arg
| arg T_PORCENTAJE arg | arg T_EXPO arg
| T_MAS arg | T_MENOS arg
| arg T_MENOR_IGUAL_MAYOR arg
| arg T_MAYOR arg | arg T_MAYOR_IGUAL arg | arg T_MENOR arg | arg T_MENOR_IGUAL arg
| arg T_DOBLE_IGUAL arg | arg T_TRIPLE_IGUAL arg | arg T_NOT_IGUAL arg
| arg T_IGUAL_NIOQUI arg | arg T_NOT_NIOQUI arg
| T_NOT arg | T_NIOQUI arg
| primary;
opt_args_comma : args
               | args T_COMA;
opt_args_or_assocs : args
                   | assocs
                   | assocs T_COMA;
recursive_elsif : 
                | T_ELSIF expr then compstmt recursive_elsif;
opt_else : 
         | T_ELSE compstmt;
rec_when_then : T_WHEN when_args then compstmt
              | rec_when_then T_WHEN when_args then compstmt;
opt_subclass : 
             | T_MENOR T_IDENTIF;
primary: T_PAR_IZQ compstmt T_PAR_DER
| literal
| variable
| primary T_CORCHETE_IZQ T_CORCHETE_DER
| primary T_CORCHETE_IZQ args T_CORCHETE_DER
| T_CORCHETE_IZQ T_CORCHETE_DER
| T_CORCHETE_IZQ args T_CORCHETE_DER
| T_LLAVE_IZQ T_LLAVE_DER
| T_LLAVE_IZQ opt_args_or_assocs T_LLAVE_DER
| T_RETURN
| T_RETURN paren_or_call_args
| function
| function T_LLAVE_IZQ opt_blockvar compstmt T_LLAVE_DER
| T_IF expr then compstmt
  recursive_elsif
  opt_else
  T_END
| T_WHILE expr T_DO compstmt T_END
| T_CASE compstmt
  rec_when_then
  opt_else
  T_END
| T_CLASS T_IDENTIF opt_subclass
    compstmt
  T_END
| T_DEF fname argdecl
    compstmt
  T_END
| T_DEF singleton T_PTO fname argdecl
    compstmt
  T_END;
opt_comma_mul_arg : 
              | T_COMA T_ASTER arg;
when_args : args opt_comma_mul_arg
          | T_ASTER arg;
then : T_FIN_INSTRUCCION
     | T_THEN
     | T_FIN_INSTRUCCION T_THEN;
do   : T_FIN_INSTRUCCION
     | T_DO
     | T_FIN_INSTRUCCION T_DO;
block_var : lhs | mlhs;
mlhs_item_list : mlhs_item
               | mlhs_item_list T_COMA mlhs_item;
opt_mul_opt_lhs : 
                | T_ASTER lhs
                | T_ASTER;
mlhs : mlhs_item_list opt_mul_opt_lhs
     | T_ASTER lhs;
mlhs_item : lhs | T_PAR_IZQ mlhs T_PAR_DER;
lhs : variable
    | primary T_CORCHETE_IZQ T_CORCHETE_DER
    | primary T_CORCHETE_IZQ args T_CORCHETE_DER
    | primary T_PTO T_IDENTIF;
mrhs : args opt_comma_mul_arg
     | T_ASTER arg;
opt_comma_assocs : 
                 | T_COMA assocs;
call_args : args opt_comma_assocs opt_comma_mul_arg //opt_comma_amp_arg
          | command;
args : arg
     | args T_COMA arg;
argdecl : T_PAR_IZQ arglist T_PAR_DER
        | arglist T_FIN_INSTRUCCION;
identifier_list : T_IDENTIF
                | identifier_list T_COMA T_IDENTIF;
opt_comma_mul_ident : 
                    | T_COMA T_ASTER
                    | T_COMA T_ASTER T_IDENTIF;
arglist : identifier_list opt_comma_mul_ident //opt_comma_amp_ident
singleton : variable
        | T_PAR_IZQ expr T_PAR_DER;
assocs : assoc
       | assocs T_COMA assoc;
assoc : arg T_THEN arg;
variable : T_IDENTIF
         | T_NIL
literal : SYMBOL
        | STRING
        | STRING2
opt_terc : 
          | T_NOT 
	  | T_FIN_INTERROGACION;
operation : T_IDENTIF opt_terc;
*/
%%
/* Llamada por yyparse ante un error */
yyerror (s) 
char *s;
{
printf ("%s\n", s); 
}
main()
{
/*Acciones a ejecutar antes del análisis*/
yyparse();
/*Acciones a ejecutar después del análisis*/
}
/* estos son reconocidos por el lexer */
/*
op_asgn : '+=' | '-=' | '*=' | '/=' | '%=' | '**='
        | '&=' | '|=' | '^=' | '<<=' | '>>='
        | '&&=' | '||=';
symbol : ':'fname | ':'varname;
fname : identifier | '..' | '|' | '^' | '&' | '<=>' | '==' | '===' | '=~'
      | '>' | '>=' | '<' | '<=' | '+' | '-' | '*' | '/' | '%' | '**'
     | '<<' | '>>' | '~' | '+@' | '-@' | '[]' | '[]=';
opt_terc : 
          | '!' | '?';
operation : identifier opt_terc;
varname : global | '@'identifier | identifier;
global : '$'identifier | '$'any_char | '$-'any_char;
string : '"' {any_char} '"'
       | '´' {any_char} '´'
       | '' {any_char} '';
STRING2 : %(Q|q|x)char {any_char} char
HERE_DOC : <<(T_IDENTIF | STRING)
{any_char}
T_IDENTIF
REGEXP : / {any_char} / [i|o|p]
| %r char {any_char} char
*/
