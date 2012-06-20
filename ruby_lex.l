%{
extern "C" {
      int yylex(void);
    }
#include "y.tab.h"
#include "ejecucion/stack.h"

struct s_node_tac {
  char var_tmp[10];
  std::list<Instruccion*> *usos;
};

typedef s_node_tac node_tac;

%}
STRING_DOBLE_CON_SALTO ([^(\"(#{)\n)]*(\\\n)*)*|(([^(\"(#{)\n)]*(\\\")*)*(\\\n)*)*
STRING_DOBLE_SIN_SALTO [^(\"(#{)\n)]*|([^(\"(#{)\n)]*(\\\")*)*
STRING_SIMPLE_CON_SALTO ([^(\'\n)]*(\\\n)*)*
STRING_SIMPLE_SIN_SALTO [^(\'\n)]*
COMMAND_CON_SALTO ([^(`\n)]*(\\\n)*)*
COMMAND_SIN_SALTO [^(`\n)]*
VARIABLE [_a-z][_a-zA-Z0-9]*|[_a-z][_a-zA-Z0-9]*\[([1-9][0-9]*|0)\]
%%
then      {return(T_THEN);};
nil      {return(T_NIL);};
puts   {return(T_PUTS);};
def     {return(T_DEF);};
end	 {return(T_END);};
return	 {return(T_RETURN);};
gets   {return(T_GETS);};
do      {return(T_DO);};
if  {return(T_IF);};
else {return(T_ELSE);};
elsif {return(T_ELSIF);};
case {return(T_CASE);};
when {return(T_WHEN);};
while {return(T_WHILE);};
class   {return(T_CLASS);};
attr_reader {return(T_ATTR_READER);};
attr_writer {return(T_ATTR_WRITER);};
attr_accessor {return(T_ACCESSOR);};
load {return(T_LOAD);};
require {return(T_REQUIRE);};
true|false {return(T_BOOL);};
= 	 {return(T_IGUAL);};
,        {return(T_COMA);};
#      {return(T_NUMERAL);};
\+       {return(T_MAS);};
\-        {return(T_MENOS);};
\*      {return(T_ASTER);};
\/       {return(T_BAR);};
\.       {return(T_PTO);};
:       {return(T_DOS_PTOS);};
\]       {return(T_CORCHETE_DER);};
\[       {return(T_CORCHETE_IZQ);};
\)       {return(T_PAR_DER);};
\(       {return(T_PAR_IZQ);};
\*\*     {return(T_EXPO);};
~       {return(T_NIOQUI);};
\%      {return(T_PORCENTAJE);};
\>      {return(T_MAYOR);};
\<      {return(T_MENOR);};
\>=    {return(T_MAYOR_IGUAL);};
\<=    {return(T_MENOR_IGUAL);};
and|&& {return(T_AND);};
or|\|\|    {return(T_OR);};
\+=       {return(T_MAS_IGUAL);};
\-=        {return(T_MENOS_IGUAL);};
not|!  {return(T_NOT);};
\?          {return(T_FIN_INTERROGACION);};
===    {return(T_TRIPLE_IGUAL);};
==      {return(T_DOBLE_IGUAL);};
\<=\> {return(T_MENOR_IGUAL_MAYOR);};
!=       {return(T_NOT_IGUAL);};
!~       {return(T_NOT_NIOQUI);};
=~  {return(T_IGUAL_NIOQUI);};
\}     {return(T_LLAVE_DER);};
\{     {return(T_LLAVE_IZQ);};
[_a-z][_a-zA-Z0-9]*\.object_id {return(T_OBJECT_ID);};
[_a-z][_a-zA-Z0-9]*\.instance_of\? {return(T_INSTANCE_OF);};
[_a-z][_a-zA-Z0-9]*\.respond_to\? {return(T_RESPOND_TO);};
[_a-z][_a-zA-Z0-9]*\.class   {return(T_INSTANCE_CLASS);};
[A-Z][_a-zA-Z0-9]*\.new   {return(T_NEW);};
{VARIABLE}\.length {return(T_LENGTH);};
{VARIABLE}\.size {return(T_SIZE);};
{VARIABLE}\.each {return(T_EACH);};
[_a-z][_a-zA-Z0-9]*\.[_a-z][_a-zA-Z0-9]* {return(T_INVOCACION_METODO);};
[A-Z][_a-zA-Z0-9]*	 {return(T_NOM_CONST);};
[_a-z][_a-zA-Z0-9]*	 {return(T_IDENTIF);};
\$[_a-z][_a-zA-Z0-9]* {return(T_IDENTIF_GLOBAL);};
@[_a-z][_a-zA-Z0-9]* {return(T_ATRIBUTO);};
:[_a-z][_a-zA-Z0-9]* {return(T_ATRIBUTO_ACCESOR);};
\$0	 {return(T_VAR_PESOS_CERO);};
\$        {return(T_VAR_PESOS);};
\$\$       {return(T_VAR_PESOS_PESOS);};
\|           {return(T_PIPE);};
([1-9][0-9]*)|0 {yylval.entero = atoi(yytext); return(T_INTEGER_ABS);};
(([1-9][0-9]*)\.[0-9]+)|(((\+|\-)?0)\.[0-9]+) {yylval.real = atof(yytext); return(T_FLOAT_ABS);};
#.*\n {;};
^=begin(.*\n)*=end {};
\'{STRING_SIMPLE_CON_SALTO}\'|\'{STRING_SIMPLE_SIN_SALTO}\' {yylval.text = strdup(yytext); return(T_STRING_1);};
\"{STRING_DOBLE_CON_SALTO}\"|\"{STRING_DOBLE_SIN_SALTO}\" {return(T_STRING_2);};
\"{STRING_DOBLE_CON_SALTO}#\{|\"{STRING_DOBLE_SIN_SALTO}#\{ {return(T_STRING_IZQ);};
\}{STRING_DOBLE_CON_SALTO}#\{|\}{STRING_DOBLE_SIN_SALTO}#\{ {return(T_STRING_CENTER);};
\}{STRING_DOBLE_CON_SALTO}\"|\}{STRING_DOBLE_SIN_SALTO}\" {return(T_STRING_DER);};
`{COMMAND_CON_SALTO}`|`{COMMAND_SIN_SALTO}` {return(T_COMMAND);};
(\n|;)* {return T_FIN_INSTRUCCION;};
\\(\t|\r|" ")*\n|\t|\r|" " {};
. {};

