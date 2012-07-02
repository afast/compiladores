%{
#include <iostream>
#include <set>

extern "C" {
      int yylex(void);
    }
#include "ejecucion/stack.h"
#include "ast.h"
#include "y.tab.h"
#define MAX_INCLUDE_DEPTH 40
int include_stack_ptr = 0;
std::set<std::string> *archivos_cargados = new std::set<std::string>();
char* replaceContinuacionLinea(char* textIn);
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
void cargarArchivo(char* textIn, int largo, bool isLoad);
%}
%option yylineno
%x load
%x require
STRING_DOBLE_CON_SALTO ([^(\"(#{)\n)]*(\\\n)*)*|(([^(\"(#{)\n)]*(\\\")*)*(\\\n)*)*
STRING_DOBLE_SIN_SALTO [^(\"(#{)\n)]*|([^(\"(#{)\n)]*(\\\")*)*
STRING_SIMPLE_CON_SALTO ([^(\'\n)]*(\\\n)*)*
STRING_SIMPLE_SIN_SALTO [^(\'\n)]*
COMMAND_CON_SALTO ([^(`\n)]*(\\\n)*)*
COMMAND_SIN_SALTO [^(`\n)]*
VARIABLE [_a-z][_a-zA-Z0-9]*|[_a-z][_a-zA-Z0-9]*\[([1-9][0-9]*|0)\]
%%
require(\t|" ")*\' {BEGIN(require);};
load(\t|" ")*\' {BEGIN(load);};
#.*\n? {};
^=begin(.*\n)*=end(" ")*\n* {;};
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
<load>[^\t|^\n]+\' { cargarArchivo(yytext, yyleng-1, true);};
<<EOF>> { 	if ( --include_stack_ptr < 0 ){
			yyterminate();
		}
		else {
			yy_delete_buffer( YY_CURRENT_BUFFER );
			yy_switch_to_buffer(include_stack[include_stack_ptr] );
		}
	};
<require>[^\t|^\n]+\' { cargarArchivo(yytext, yyleng-1, false);};
true {yylval.entero = 1; return(T_BOOL);};
false {yylval.entero = 0; return(T_BOOL);};
ARGV {yylval.text = strdup(yytext); return(T_VAR_ARGV);};
= 	 {return(T_IGUAL);};
,        {return(T_COMA);};
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
[_a-z][_a-zA-Z0-9]*\.object_id {yylval.text = strdup(yytext); return(T_OBJECT_ID);};
[_a-z][_a-zA-Z0-9]*\.instance_of\? {yylval.text = strdup(yytext); return(T_INSTANCE_OF);};
[_a-z][_a-zA-Z0-9]*\.respond_to\? {yylval.text = strdup(yytext); return(T_RESPOND_TO);};
[_a-z][_a-zA-Z0-9]*\.class   {yylval.text = strdup(yytext); return(T_INSTANCE_CLASS);};
[A-Z][_a-zA-Z0-9]*\.new   {yylval.text = strdup(yytext); return(T_NEW);};
{VARIABLE}\.length {yylval.text = strdup(yytext); return(T_LENGTH);};
{VARIABLE}\.size {yylval.text = strdup(yytext); return(T_SIZE);};
{VARIABLE}\.each {yylval.text = strdup(yytext); return(T_EACH);};
{VARIABLE}\.[_a-z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); return(T_INVOCACION_METODO);};
[A-Z][_a-zA-Z0-9]*	 {yylval.text = strdup(yytext); return(T_NOM_CONST);};
[_a-z][_a-zA-Z0-9]*	 {yylval.text = strdup(yytext); return(T_IDENTIF);};
\$[_a-z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); return(T_IDENTIF_GLOBAL);};
@[_a-z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); return(T_ATRIBUTO);};
:[_a-z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); return(T_ATRIBUTO_ACCESOR);};
\$0	 {yylval.text = strdup(yytext); return(T_VAR_PESOS_CERO);};
\$:        {yylval.text = strdup(yytext); return(T_VAR_PESOS);};
\$\$       {yylval.text = strdup(yytext); return(T_VAR_PESOS_PESOS);};
\|           {return(T_PIPE);};
([1-9][0-9]*)|0 {yylval.entero = atoi(yytext); return(T_INTEGER_ABS);};
(([1-9][0-9]*)\.[0-9]+)|(((\+|\-)?0)\.[0-9]+) {yylval.real = atof(yytext); return(T_FLOAT_ABS);};
\'{STRING_SIMPLE_CON_SALTO}\'|\'{STRING_SIMPLE_SIN_SALTO}\' {yylval.text = replaceContinuacionLinea(yytext); return(T_STRING_1);};
\"{STRING_DOBLE_CON_SALTO}\"|\"{STRING_DOBLE_SIN_SALTO}\"   {yylval.text = replaceContinuacionLinea(yytext); return(T_STRING_2);};
\"{STRING_DOBLE_CON_SALTO}#\{|\"{STRING_DOBLE_SIN_SALTO}#\{ {yylval.text = replaceContinuacionLinea(yytext); return(T_STRING_IZQ);};
\}{STRING_DOBLE_CON_SALTO}#\{|\}{STRING_DOBLE_SIN_SALTO}#\{ {yylval.text = replaceContinuacionLinea(yytext); return(T_STRING_CENTER);};
\}{STRING_DOBLE_CON_SALTO}\"|\}{STRING_DOBLE_SIN_SALTO}\"   {yylval.text = replaceContinuacionLinea(yytext); return(T_STRING_DER);};
`{COMMAND_CON_SALTO}`|`{COMMAND_SIN_SALTO}` {yylval.text = replaceContinuacionLinea(yytext); return(T_COMMAND);};
(\n|;)* {return T_FIN_INSTRUCCION;};
\t|\r|" " {}
\\(\t|\r|" ")*\n {};
. {};
%%
void cargarArchivo(char* textIn, int largo, bool isLoad){
// obtiene el nombre de fichero a incluir
char* text = strndup(textIn, largo);
text = strcat(text, ".rb");
std::string *nombre = new std::string(text);
char* text2 = strndup(textIn, largo);
std::string *nombre2 = new std::string(text2);
if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
{
	fprintf( stderr, "Demasiados load(require) anidados" );
	exit( 1 );
}
include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
if((isLoad) || ((archivos_cargados->count(*nombre) == 0) && (archivos_cargados->count(*nombre2) == 0))){
	yyin = fopen( text, "r" );
	if (!yyin){
		yyin = fopen( text2, "r" );
		if(!yyin) {
			fprintf( stderr, "No se encontraron los archivos %s o %s\n", text, text2);
			exit( 1 );
		} else {
			if(!isLoad){
				archivos_cargados->insert(*nombre2);
			}
		}
	} else {
		if(!isLoad){
			archivos_cargados->insert(*nombre);
		}
	}
}
yy_switch_to_buffer(yy_create_buffer( yyin, YY_BUF_SIZE ) );	
BEGIN(INITIAL);	
}

char* replaceContinuacionLinea(char* textIn){
	std::string *tmp = new std::string(textIn);
	int n = tmp->find("\\\n");
	while (n>0){
    		tmp->erase(n, 2);
    		n = tmp->find("\\\n");
  	}
	char * result = new char[tmp->size() + 1];
	std::copy(tmp->begin(), tmp->end(), result);
	result[tmp->size()] = '\0';
	delete tmp;
	return result;
}
/*
char* scapeSecuence(char* textIn){
	std::string *tmp = new std::string(textIn);
	int n = tmp->find("\\\n");
	while (n>0){
    		tmp->erase(n, 2);
    		n = tmp->find("\\\n");
  	}
	char * result = new char[tmp->size() + 1];
	std::copy(tmp->begin(), tmp->end(), result);
	result[tmp->size()] = '\0';
	delete tmp;
	return result;
}
*/


