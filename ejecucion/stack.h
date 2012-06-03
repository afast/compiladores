enum code_ops { FIN, PUTS, GETS }; 

struct instruccion {
  enum code_ops op;
  void *arg1, *arg2, *arg3;
};

void ejecutar(struct instruccion *codigo);
