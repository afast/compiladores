%{
/* fichero instrucciones.y */
#include <stdio.h>
%}
%start program
%token T_PTO_COMA tNEWLINE T_DO T_PIPE T_END T_IF T_WHILE T_LLAVE_IZQ T_LLAVE_DER
%token T_RETURN T_AND T_OR T_NOT T_PAR_IZQ T_PAR_DER T_MAS T_MENOS
%token T_ASTER T_EXPO T_BAR T_PORCENTAJE T_MENOR_IGUAL_MAYOR T_MAYOR T_MAS_IGUAL T_MENOR T_MENOS_IGUAL
%token T_DOBLE_IGUAL T_TRIPLE_IGUAL T_NOT_IGUAL T_IGUAL_NIOQUI T_NOT_NIOQUI T_NIOQUI
%token T_ELSE T_ELSIF T_CLASS T_DEF T_COMA T_PTO T_DOS_PTOS T_THEN
%token T_CORCHETE_IZQ T_CORCHETE_DER T_NIL 
%token T_CASE STRING STRING2 SYMBOL VARNAME T_WHEN fname T_IDENTIF
%token T_IGUAL T_FIN_INTERROGACION
%token T_PUTS T_LENGTH T_GETS T_NEW T_SIZE T_EACH T_OBJECT_ID T_RESPOND_TO
%token T_INSTANCE_OF T_ATTR_READER T_ATTR_WRITER T_ACCESSOR T_LOAD T_REQUIRE
%token T_ARGV T_BOOL T_ANTI_BAR T_NUMERAL T_MAYOR_IGUAL T_MENOR_IGUAL T_IDENTIF_GLOBAL
%token T_ATRIBUTO T_VAR_PESOS_CERO T_VAR_PESOS T_VAR_PESOS_PESOS T_INTEGER
%token T_FLOAT T_STRING_1 T_STRING_2 T_STRING_IZQ T_STRING_DER T_COMMAND T_ESPACIOS T_ERROR
/*=========================================================================
                          OPERATOR PRECEDENCE
=========================================================================*/
%left T_MENOS T_MAS
%left T_ASTER T_BAR
%%
program : compstmt;
t : T_PTO_COMA | '\n';
opt_t : 
     | t;
compstmt : stmt
         | stmt t
         | stmt texpr
         | stmt texpr t;
texpr : t expr
      | texpr t expr;
def_blockvar :T_PIPE block_var T_PIPE;
opt_blockvar :
             | def_blockvar;
opt_block : /* empty */
         | T_DO opt_blockvar compstmt T_END;
stmt : call T_DO opt_blockvar compstmt T_END
| stmt T_IF expr
| stmt T_WHILE expr
| lhs T_IGUAL command opt_block
| expr
;
expr : mlhs T_IGUAL mrhs
    | T_RETURN call_args
    | expr T_AND expr
    | expr T_OR expr
    | T_NOT expr
    | command
    | T_NOT command
    | arg
;
call : function
    | command
;
command : operation call_args
 | primary T_PTO operation call_args
;
paren_or_call_args : T_PAR_IZQ T_PAR_DER
              | T_PAR_IZQ call_args T_PAR_DER;
opt_call_args : /* empty */
              | paren_or_call_args;
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

opt_args : /* empty */
         | args;
opt_args_comma : opt_args
               | args T_COMA;
opt_args_or_assocs : args
                   | assocs
                   | assocs T_COMA;
recursive_elsif : /* empty */
                | T_ELSIF expr then compstmt recursive_elsif;
opt_else : /* empty */
         | T_ELSE compstmt;
rec_when_then : T_WHEN when_args then compstmt
              | rec_when_then T_WHEN when_args then compstmt;
opt_subclass : /* empty */
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
| T_DEF singleton point_or_doublecolon fname argdecl
    compstmt
  T_END;
point_or_doublecolon : T_PTO
//                     | tDOUBLECOLON;
opt_comma_mul_arg : /* empty */
              | T_COMA T_ASTER arg;
when_args : args opt_comma_mul_arg
          | T_ASTER arg;
then : t    /*"then" and "do" can go on next line*/
     | T_THEN
     | t T_THEN;
do   : t
     | T_DO
     | t T_DO;
block_var : lhs | mlhs;
mlhs_item_list : mlhs_item
               | mlhs_item_list T_COMA mlhs_item;
opt_mul_opt_lhs : /* empty */
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
opt_comma_assocs : /* empty */
                 | T_COMA assocs;
call_args : args opt_comma_assocs opt_comma_mul_arg //opt_comma_amp_arg
          | command;
args : arg
     | args T_COMA arg;
argdecl : T_PAR_IZQ arglist T_PAR_DER
        | arglist t;
identifier_list : T_IDENTIF
                | identifier_list T_COMA T_IDENTIF;
opt_comma_mul_ident : /* empty */
                    | T_COMA T_ASTER
                    | T_COMA T_ASTER T_IDENTIF;
arglist : identifier_list opt_comma_mul_ident //opt_comma_amp_ident
singleton : variable
        | T_PAR_IZQ expr T_PAR_DER;
assocs : assoc
       | assocs T_COMA assoc;
assoc : arg T_THEN arg;
variable : VARNAME
         | T_NIL
//         | SELF;
literal : SYMBOL
        | STRING
        | STRING2
opt_terc : /* empty */
          | T_NOT 
	  | T_FIN_INTERROGACION;
operation : T_IDENTIF opt_terc;
%%
yyerror (s) /* Llamada por yyparse ante un error */
char *s;
{
printf ("%s\n", s); /* Esta implementación por defecto nos valdrá */
/* Si no creamos esta función, habrá que enlazar con –ly en el
momento de compilar para usar una implementación por defecto */
}
main()
{
/*Acciones a ejecutar antes del análisis*/
yyparse();
/*Acciones a ejecutar después del análisis*/
}

