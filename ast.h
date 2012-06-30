#ifndef _AST_H
#define _AST_H

#include <iostream>
#include <list>

enum ast_node_t {
  c_if, op_mul, op_plus, op_div, op_sub, op_pow, op_mod, op_asgn, c_elsif,
  c_while, f_string, f_entero, f_decimal, f_bool, t_puts, t_compstmt,
  t_identif, t_atributo, t_arr_place, t_gets, t_command, t_method_call,
  t_nil, t_mul_string, t_add_string, t_method_with_args, t_args,
  b_and, b_or, b_not, b_mayor, b_mayor_igual, b_menor, b_menor_igual,
  b_doble_igual, b_not_igual, b_is_bool
};

struct ast_node {
  enum ast_node_t tipo;
  struct ast_node *h1, *h2, *h3, *h4;
  std::list<struct ast_node*> *stmt_list;
  char *str;
  long int entero;
  double decimal;
  bool booleano;
  int linea;
};

typedef struct ast_node ast;

ast* new_numeric_op(enum ast_node_t op, ast* left, ast* right, int linea);
ast* new_number(long int number, int linea);
ast* new_number(double number, int linea);
ast* new_puts(ast* t, int linea);
ast* new_compstmt(ast* t);
ast* add_stmt_compstmt(ast* stmt, ast* compstmt);
ast* add_front_stmt_compstmt(ast* stmt, ast* compstmt);
ast* new_identificador(char* name, int linea);
ast* new_atributo(char* name, int linea);
ast* new_array_pos(char* name, int place, int linea);
ast* new_gets(int linea);;
ast* new_string(char* texto, int linea);
ast* new_command(char* texto, int linea);
ast* new_object_call(char* llamada, int linea);
ast* new_nil(int linea);;
ast* new_mul_string(ast* texto, ast* numero, int linea);
ast* new_add_string(ast* string1, ast* string2, int linea);
ast* new_object_call(char* funcion, ast* args, int linea);
ast* new_arguments(ast* arg, int linea);
ast* add_argument(ast* arg, ast* args, int linea);
ast* new_boolean_op(enum ast_node_t op, ast* left, ast* right, int linea);
ast* new_bool(int b, int linea);
ast* new_if(ast* cond, ast* compstmt, ast* opt_rec_elsif, ast* opt_else, int linea);
ast* new_elsif(ast* cond, ast* compstmt, ast* opt_rec_elsif, int linea);
ast* new_asgn(ast* variable, ast* valor, int linea);
ast* new_while(ast* cond, ast* compstmt, int linea);

#endif
