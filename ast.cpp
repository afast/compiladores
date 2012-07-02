#include "ast.h"

ast* new_numeric_op(enum ast_node_t op, ast* left, ast* right, int linea){
  ast* res = new ast;
  res->linea = linea;
  res->tipo= op;
  res->h1= left;
  res->h2= right;
  return res;
}

ast* new_number(long int number, int linea){

std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX             " << number << std::endl; 
  ast* res = new ast;
  res->tipo = f_entero;
  res->linea = linea;
  res->entero = number;
  return res;
}

ast* new_number(double number, int linea){
  ast* res = new ast;
  res->tipo = f_decimal;
  res->linea = linea;
  res->decimal = number;
  return res;
}

ast* new_puts(ast* t, int linea){
  ast* res = new ast;
  res->tipo = t_puts;
  res->linea = linea;
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

ast* new_identificador(char* name, int linea){
  ast* res = new ast;
  res->tipo = t_identif;
  res->linea = linea;
  res->str = name;
  return res;
}

ast* new_identificador_global(char* name, int linea){
  ast* res = new ast;
  res->tipo = t_identif;
  res->linea = linea;
  res->str = name;
  return res;
}

ast* new_atributo(char* name, int linea){
  ast* res = new ast;
  res->tipo = t_atributo;
  res->linea = linea;
  res->str = name;
  return res;
}

ast* new_array_pos(char* name, ast* place, int linea){
  ast* res = new ast;
  res->tipo = t_arr_place;
  res->linea = linea;
  res->str = name;
std::cout << "nombre: " << name << std::endl;
  res->h1 = place;
std::cout << "place: " << place << std::endl;
  return res;
}

ast* new_gets(int linea){
  ast* res = new ast;
  res->tipo = t_gets;
  res->linea = linea;
  return res;
}

ast* new_string(char* texto, int linea){
  ast* res = new ast;
  res->tipo = f_string;
  res->linea = linea;
  res->str = texto;
  return res;
}

ast* new_command(char* texto, int linea){
  ast* res = new ast;
  res->tipo = t_command;
  res->linea = linea;
  res->str = texto;
  return res;
}

ast* new_object_call(char* llamada, int linea){
  ast* res = new ast;
  res->tipo = t_method_call;
  res->linea = linea;
  res->str = llamada;
  return res;
}

ast* new_nil(int linea){
  ast* res = new ast;
  res->tipo = t_nil;
  res->linea = linea;
  return res;
}

ast* new_mul_string(ast* texto, ast* numero, int linea){
  ast* res = new ast;
  res->tipo = t_mul_string;
  res->linea = linea;
  res->h1 = texto;
  res->h2 = numero;
  return res;
}

ast* new_add_string(ast* string1, ast* string2, int linea){
  ast* res = new ast;
  res->tipo = t_add_string;
  res->linea = linea;
  res->h1 = string1;
  res->h2 = string2;
  return res;
}

ast* new_object_call(char* funcion, ast* args, int linea){
  ast* res = new ast;
  res->tipo = t_method_with_args;
  res->linea = linea;
  res->str = funcion;
  res->h1 = args;
  return res;
}

ast* new_arguments(ast* arg, int linea){
  ast* res = new ast;
  res->tipo = t_args;
  res->linea = linea;
  res->stmt_list = new std::list<ast*>;
  res->stmt_list->push_back(arg);
  return res;
}

ast* add_argument(ast* arg, ast* args, int linea){
  args->stmt_list->push_back(arg);
  return args;
}

ast* new_boolean_op(enum ast_node_t op, ast* left, ast* right, int linea){
  ast* res = new ast;
  res->tipo = op;
  res->linea = linea;
  res->h1 = left;
  res->h2 = right;
  return res;
}

ast* new_bool(int b, int linea){
  ast* res = new ast;
  res->tipo = f_bool;
  res->linea = linea;
  res->booleano = (b != 0);
  return res;
}

ast* new_if(ast* cond, ast* compstmt, ast* opt_rec_elsif, ast* opt_else, int linea){
  ast* res = new ast;
  res->tipo = c_if;
  res->linea = linea;
  res->h1 = cond;
  res->h2 = compstmt;
  res->h3 = opt_rec_elsif;
  res->h4 = opt_else;
  return res;
}

ast* new_elsif(ast* cond, ast* compstmt, ast* opt_rec_elsif, int linea) {
  ast* res = new ast;
  res->tipo = c_elsif;
  res->linea = linea;
  res->h1 = cond;
  res->h2 = compstmt;
  res->h3 = opt_rec_elsif;
  return res;
}

ast* new_asgn(ast* variable, ast* valor, int linea){
  ast* res = new ast;
  res->tipo = op_asgn;
  res->linea = linea;
  res->h1 = variable;
  res->h2 = valor;
  return res;
}

ast* new_while(ast* cond, ast* compstmt, int linea){
  ast* res = new ast;
  res->tipo = c_while;
  res->linea = linea;
  res->h1 = cond;
  res->h2 = compstmt;
  return res;
}

ast* new_case(ast* cond, ast* value, ast* when_rec) {
  ast* res = new ast;
  res->tipo = c_case;
  res->h1 = cond;
  res->h2 = value;
  res->h3 = when_rec;
  return res;
}

ast* new_when_rec(ast* cond, ast* value, ast* when_rec) {
  ast* res = new ast;
  res->tipo = c_case_rec;
  res->h1 = cond;
  res->h2 = value;
  res->h3 = when_rec;
  return res;
}

ast* new_method(char* name, ast* args, ast* comp_stmt, int linea){
  ast* res = new ast;
  res->tipo = a_method; //method defined
  res->linea = linea;
  res->h1 = args; //puede ser NULL
  res->h2 = comp_stmt; //Lineas del metodo
  res->str = name; //nombre del metodo
  return res;
}

ast* new_method_call(char* variable, ast* args, int linea){
  ast* res = new ast;
  res->tipo = call_method;
  res->linea = linea;
  res->str = variable;
  res->h1 = args; //puede ser NULL
  return res;
}

ast* new_params(ast* param, int linea){
  ast* res = new ast;
  res->tipo = t_params;
  res->linea = linea;
  res->stmt_list = new std::list<ast*>;
  res->stmt_list->push_back(param);
  return res;
}

ast* add_param(ast* args, ast* arg, int linea){
  args->stmt_list->push_back(arg);
  return args;
}

ast* new_class(char* name, ast* compstmt, int linea){
  ast* res = new ast;
  res->tipo = t_class;
  res->linea = linea;
  res->str = name;
  res->h1 = compstmt;
  return res;
}

ast* new_class_method_call(char* name, ast* params, int linea){
  ast* res = new ast;
  std::string* aux = new std::string(name);
  int pos = aux->find('.');
  res->tipo = instance_method_call;
  res->linea = linea;
  char* method = new char[aux->size()-pos-1];
  res->str = new char[pos];
  aux->copy(method, aux->size(), pos+1);
  aux->copy(res->str, pos, 0);
  std::cout << res->str << std::endl;
  std::cout << method << std::endl;
  res->h1 = new_object_call(method, linea);
  res->h2 = params;
  delete aux;
  return res;
}

ast* new_class_new(char* class_name, ast* params, int linea){
  ast* res = new ast;
  std::string* aux = new std::string(class_name);
  int pos = aux->find('.');
  res->tipo = method_call_new;
  res->linea = linea;
  res->str = new char[pos];
  aux->copy(res->str, pos, 0);
  std::cout << "callging " << res->str << ".new" << std::endl;
  res->h1 = params;
  delete aux;
  return res;
}

ast* new_accesores(char* atributo, int linea){
  ast* res = new ast;
  res->tipo = t_accesor;
  res->linea = linea;
  res->str = atributo;
  ast* lista = new ast;
  lista->tipo = t_accesores;
  lista->stmt_list = new std::list<ast*>;
  lista->stmt_list->push_back(res);
  return lista;
}

ast* new_accesores(char* atributo, ast* accesores, int linea){
  ast* res = new ast;
  res->tipo = t_accesor;
  res->linea = linea;
  res->str = atributo;
  accesores->stmt_list->push_back(res);
  return accesores;
}

ast* new_accesor_list(enum ast_node_t tipo, ast* lista, int linea){
  ast* res = new ast;
  res->tipo = tipo;
  res->linea = linea;
  res->h1 = lista;
  return res;
}

ast* new_class_attr_assign(char* var_attr, ast* value, int linea){
  ast* res = new ast;
  std::string* aux = new std::string(var_attr);
  int pos = aux->find('.');
  char* method = new char[aux->size()-pos-1];
  res->str = new char[pos];
  aux->copy(method, aux->size(), pos+1);
  aux->copy(res->str, pos, 0);
  std::cout << res->str << std::endl;
  std::cout << method << std::endl;
  res->h1 = new_object_call(method, linea);
  res->h2 = value;
  res->tipo = t_attr_assign;
  res->linea = linea;
  return res;
}
