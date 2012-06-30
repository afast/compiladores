#ifndef _AST_H
#define _AST_H

#include <iostream>
#include <list>

enum ast_node_t {
  c_if, op_mul, op_plus, op_div, op_sub, op_pow, op_mod, c_elsif,
  c_while, f_string, f_entero, f_decimal, f_bool, t_puts, t_compstmt,
  t_identif, t_atributo, t_arr_place, t_gets, t_command, t_method_call,
  t_nil, t_mul_string, t_add_string, t_method_with_args, t_args,
  b_and, b_or, b_not, b_mayor, b_mayor_igual, b_menor, b_menor_igual,
  b_doble_igual, b_not_igual, b_is_bool, c_case, c_case_rec
};

struct ast_node {
  enum ast_node_t tipo;
  struct ast_node *h1, *h2, *h3, *h4;
  std::list<struct ast_node*> *stmt_list;
  char *str;
  long int entero;
  double decimal;
  bool booleano;
};

typedef struct ast_node ast;

ast* new_numeric_op(enum ast_node_t op, ast* left, ast* right);
ast* new_number(long int number);
ast* new_number(double number);
ast* new_puts(ast* t);
ast* new_compstmt(ast* t);
ast* add_stmt_compstmt(ast* stmt, ast* compstmt);
ast* add_front_stmt_compstmt(ast* stmt, ast* compstmt);
ast* new_identificador(char* name);
ast* new_atributo(char* name);
ast* new_array_pos(char* name, int place);
ast* new_gets();
ast* new_string(char* texto);
ast* new_command(char* texto);
ast* new_object_call(char* llamada);
ast* new_nil();
ast* new_mul_string(ast* texto, int numero);
ast* new_add_string(ast* string1, ast* string2);
ast* new_object_call(char* funcion, ast* args);
ast* new_arguments(ast* arg);
ast* add_argument(ast* arg, ast* args);
ast* new_boolean_op(enum ast_node_t op, ast* left, ast* right);
ast* new_bool(int b);
ast* new_if(ast* cond, ast* compstmt, ast* opt_rec_elsif, ast* opt_else);
ast* new_elsif(ast* cond, ast* compstmt, ast* opt_rec_elsif);
ast* new_while(ast* cond, ast* compstmt);
ast* new_case(ast* cond, ast* value, ast* when_rec);
ast* new_when_rec(ast* cond, ast* value, ast* when_rec);

#endif
