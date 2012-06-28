#include "ast.h"

ast* new_numeric_op(enum ast_node_t op, ast* left, ast* right){
  ast* res = new ast;
  res->tipo= op;
  res->h1= left;
  res->h2= right;
  return res;
}

ast* new_number(long int number){
  ast* res = new ast;
  res->tipo = f_entero;
  res->entero = number;
  return res;
}

ast* new_number(double number){
  ast* res = new ast;
  res->tipo = f_decimal;
  res->decimal = number;
  return res;
}

ast* new_puts(ast* t){
  ast* res = new ast;
  res->tipo = t_puts;
  res->h1 = t;
  return res;
}

ast* new_compstmt(ast* t){
  if (t == NULL)
    return NULL;
  ast* res = new ast;
  res->tipo = t_compstmt;
  res->stmt_list = new std::list<ast*>;
  res->stmt_list->push_back(t);
  return res;
}

ast* add_stmt_compstmt(ast* stmt, ast* compstmt){
  if (compstmt == NULL)
    return new_compstmt(stmt);
  compstmt->stmt_list->push_back(stmt);
  return compstmt;
}

ast* add_front_stmt_compstmt(ast* stmt, ast* compstmt){
  if (compstmt == NULL)
    return new_compstmt(stmt);
  compstmt->stmt_list->push_front(stmt);
  return compstmt;
}

ast* new_identificador(char* name){
  ast* res = new ast;
  res->tipo = t_identif;
  res->str = name;
  return res;
}

ast* new_atributo(char* name){
  ast* res = new ast;
  res->tipo = t_atributo;
  res->str = name;
  return res;
}

ast* new_array_pos(char* name, int place){
  ast* res = new ast;
  res->tipo = t_arr_place;
  res->str = name;
  res->entero = place;
  return res;
}

ast* new_gets(){
  ast* res = new ast;
  res->tipo = t_gets;
  return res;
}

ast* new_string(char* texto){
  ast* res = new ast;
  res->tipo = f_string;
  res->str = texto;
  return res;
}

ast* new_command(char* texto){
  ast* res = new ast;
  res->tipo = t_command;
  res->str = texto;
  return res;
}

ast* new_object_call(char* llamada){
  ast* res = new ast;
  res->tipo = t_method_call;
  res->str = llamada;
  return res;
}

ast* new_nil(){
  ast* res = new ast;
  res->tipo = t_nil;
  return res;
}

ast* new_mul_string(ast* texto, int numero){
  ast* res = new ast;
  res->tipo = t_mul_string;
  res->h1 = texto;
  res->entero = numero;
  return res;
}

ast* new_add_string(ast* string1, ast* string2){
  ast* res = new ast;
  res->tipo = t_add_string;
  res->h1 = string1;
  res->h2 = string2;
  return res;
}

ast* new_object_call(char* funcion, ast* args){
  ast* res = new ast;
  res->tipo = t_method_with_args;
  res->str = funcion;
  res->h1 = args;
  return res;
}

ast* new_arguments(ast* arg){
  ast* res = new ast;
  res->tipo = t_args;
  res->stmt_list = new std::list<ast*>;
  res->stmt_list->push_back(arg);
  return res;
}

ast* add_argument(ast* arg, ast* args){
  args->stmt_list->push_back(arg);
  return args;
}

ast* new_boolean_op(enum ast_node_t op, ast* left, ast* right){
  ast* res = new ast;
  res->tipo = op;
  res->h1 = left;
  res->h2 = right;
  return res;
}

ast* new_bool(int b){
  ast* res = new ast;
  res->tipo = f_bool;
  res->booleano = (b != 0);
  return res;
}

ast* new_if(ast* cond, ast* compstmt, ast* opt_rec_elsif, ast* opt_else){
  ast* res = new ast;
  res->tipo = c_if;
  res->h1 = cond;
  res->h2 = compstmt;
  res->h3 = opt_rec_elsif;
  res->h4 = opt_else;
  return res;
}

ast* new_elsif(ast* cond, ast* compstmt, ast* opt_rec_elsif) {
  ast* res = new ast;
  res->tipo = c_elsif;
  res->h1 = cond;
  res->h2 = compstmt;
  res->h3 = opt_rec_elsif;
  return res;
}

ast* new_asgn(ast* variable, ast* valor){
  ast* res = new ast;
  res->tipo = op_asgn;
  res->h1 = variable;
  res->h2 = valor;
  return res;
}
