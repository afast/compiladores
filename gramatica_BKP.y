%start program
%token tSEMICOLON tNEWLINE DO tPIPE END UNDEF ALIAS IF WHILE UNLESS UNTIL BEGIN tLBRACE tRBRACE
%token RETURN YIELD AND OR NOT tNOT SUPER tLPAREN tRPAREN tTWOPOINTS tTHREEPOINTS tPLUS tMINUS
%token tMUL tTWOMUL tDIV tPERCENT tEXP tCARET tAMP tEQUIV tGREATER tGREATEREQ tLESS tLESSEQ
%token tEQUALS tTHREEEQUALS tDIFF tEQTILDE tNOTTILDE tTILDE tPUSH tSHIFT tBAND tBOR tDEFINED
%token ELSE ELSIF FOR IN RESCUE ENSURE CLASS MODULE DEF tCOMMA tPOINT tDOUBLECOLON tCOLON THEN
%token tLBRACKET tRBRACKET NIL SELF tTHEN NUMERIC tPLUSASGN tMINUSASGN tMULASGN tDIVASGN
%token CASE HERE_DOC REGEXP STRING STRING2 SYMBOL VARNAME WHEN fname IDENTIFIER
%token OP_ASGN tBEGIN tEND
/*=========================================================================
                          OPERATOR PRECEDENCE
=========================================================================*/
%left '-' '+'
%left '*' '/'
%right '^'
%%
program : compstmt;
t : ';' | '\n';
opt_t : /* empty */
     | t;
compstmt : stmt
         | stmt t
         | stmt texpr
         | stmt texpr t;
texpr : t expr
      | texpr t expr;
def_blockvar :'|' block_var '|';
opt_blockvar : /* empty */
             | def_blockvar;
opt_block : /* empty */
         | DO opt_blockvar compstmt END;
stmt : call DO opt_blockvar compstmt END
| UNDEF fname
| ALIAS fname fname
| stmt IF expr
| stmt WHILE expr
| stmt UNLESS expr
| stmt UNTIL expr
| tBEGIN '{' compstmt '}' /*object initializer*/
| tEND '{' compstmt '}' /*object finalizer*/
| lhs '=' command opt_block
| expr
;
expr : mlhs '=' mrhs
    | RETURN call_args
    | YIELD call_args
    | expr AND expr
    | expr OR expr
    | NOT expr
    | command
    | '!' command
    | arg
;
call : function
    | command
;
command : operation call_args
 | primary'.'operation call_args
 | primary tDOUBLECOLON operation call_args
 | SUPER call_args
;
paren_or_call_args : '(' ')'
              | '(' call_args ')';
opt_call_args : /* empty */
              | paren_or_call_args;
function : operation
         | operation paren_or_call_args
         | primary '.' operation
         | primary '.' operation paren_or_call_args
         | primary tDOUBLECOLON operation
         | primary tDOUBLECOLON operation paren_or_call_args
         | SUPER
         | SUPER paren_or_call_args;
arg : lhs '=' arg
| lhs OP_ASGN arg
| arg tTWOPOINTS arg | arg tTHREEPOINTS arg
| arg '+' arg | arg '-' arg | arg '*' arg | arg '/' arg
| arg '%' arg | arg tTWOMUL arg
| '+' arg | '-' arg
| arg '|' arg
| arg '^' arg | arg '&' arg
| arg tEQUIV arg
| arg '>' arg | arg tGREATEREQ arg | arg '<' arg | arg tLESSEQ arg
| arg tEQUALS arg | arg tTHREEEQUALS arg | arg tDIFF arg
| arg tEQTILDE arg | arg tNOTTILDE arg
| '!' arg | '~' arg
| arg tPUSH arg | arg tSHIFT arg
| arg tBAND arg | arg tBOR arg
| tDEFINED arg
| primary;

opt_args : /* empty */
         | args;
opt_args_comma : opt_args
               | args ',';
opt_args_or_assocs : args
                   | assocs
                   | assocs ',';
recursive_elsif : /* empty */
                | ELSIF expr then compstmt recursive_elsif;
opt_else : /* empty */
         | ELSE compstmt;
rec_when_then : WHEN when_args then compstmt
              | rec_when_then WHEN when_args then compstmt;
rec_rescue : /* empty */
           | rec_rescue RESCUE opt_args do compstmt;
opt_ensure : /* empty */
           | ENSURE compstmt;
opt_subclass : /* empty */
             | '<' IDENTIFIER;
primary: '(' compstmt ')'
| literal
| variable
| primary tDOUBLECOLON IDENTIFIER
| tDOUBLECOLON IDENTIFIER
| primary '[' ']'
| primary '[' args ']'
| '[' ']'
| '[' args ']'
| '{' '}'
| '{' opt_args_or_assocs '}'
| RETURN
| RETURN paren_or_call_args
| YIELD
| YIELD paren_or_call_args
| tDEFINED '(' arg ')'
| function
| function '{' opt_blockvar compstmt '}'
| IF expr then compstmt
  recursive_elsif
  opt_else
  END
| UNLESS expr then
  compstmt
  opt_else
  END
| WHILE expr do compstmt END
| UNTIL expr do compstmt END
| CASE compstmt
  rec_when_then
  opt_else
  END
| FOR block_var IN expr do
    compstmt
  END
| BEGIN
    compstmt
    rec_rescue
    opt_else
    opt_ensure
  END
| CLASS IDENTIFIER opt_subclass
    compstmt
  END
| MODULE IDENTIFIER
    compstmt
  END
| DEF fname argdecl
    compstmt
  END
| DEF singleton point_or_doublecolon fname argdecl
    compstmt
  END;
point_or_doublecolon : '.'
                     | tDOUBLECOLON;
opt_comma_mul_arg : /* empty */
              | ',' '*' arg;
when_args : args opt_comma_mul_arg
          | '*' arg;
then : t    /*"then" and "do" can go on next line*/
     | THEN
     | t THEN;
do   : t
     | DO
     | t DO;
block_var : lhs | mlhs;
mlhs_item_list : mlhs_item
               | mlhs_item_list ',' mlhs_item;
opt_mul_opt_lhs : /* empty */
                | '*' lhs
                | '*';
mlhs : mlhs_item_list opt_mul_opt_lhs
     | '*' lhs;
mlhs_item : lhs | '(' mlhs ')';
lhs : variable
    | primary '[' ']'
    | primary '[' args ']'
    | primary '.' IDENTIFIER;
mrhs : args opt_comma_mul_arg
     | '*' arg;
opt_comma_assocs : /* empty */
                 | ',' assocs;
opt_comma_amp_arg : /* empty */
                  | ',' '&' arg;
call_args : args opt_comma_assocs opt_comma_mul_arg opt_comma_amp_arg
          | assocs opt_comma_mul_arg opt_comma_amp_arg
          | '*' arg opt_comma_amp_arg | '&' arg
          | command;
args : arg
     | args ',' arg;
argdecl : '(' arglist ')'
        | arglist t;
identifier_list : IDENTIFIER
                | identifier_list ',' IDENTIFIER;
opt_comma_mul_ident : /* empty */
                    | ',' '*'
                    | ',' '*' IDENTIFIER;
opt_comma_amp_ident : /* empty */
                    | ',' '&'IDENTIFIER;
opt_amp_ident : /* empty */
              | '&'IDENTIFIER;
arglist : identifier_list opt_comma_mul_ident opt_comma_amp_ident
        | '*'IDENTIFIER opt_comma_amp_ident
        | opt_amp_ident;
singleton : variable
        | '(' expr ')';
assocs : assoc
       | assocs ',' assoc;
assoc : arg tTHEN arg;
variable : VARNAME
         | NIL
         | SELF;
literal : NUMERIC
        | SYMBOL
        | STRING
        | STRING2
        | HERE_DOC
        | REGEXP;
opt_terc : /* empty */
          | '!' | '?';
operation : IDENTIFIER opt_terc;
%%
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
HERE_DOC : <<(IDENTIFIER | STRING)
{any_char}
IDENTIFIER
REGEXP : / {any_char} / [i|o|p]
| %r char {any_char} char
IDENTIFIER : sequence in /[a-zA-Z_]{a-zA-Z0-9_}/.
*/
