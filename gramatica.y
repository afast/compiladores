%start program
%token tSEMICOLON tNEWLINE DO tPIPE END UNDEF ALIAS IF WHILE UNLESS UNTIL BEGIN tLBRACE tRBRACE
%token RETURN YIELD AND OR NOT tNOT SUPER tLPAREN tRPAREN tTWOPOINTS tTHREEPOINTS tPLUS tMINUS
%token tMUL tDIV tPERCENT tEXP tCARET tAMP tEQUIV tGREATER tGREATEREQ tLESS tLESSEQ
%token tEQUALS tTHREEEQUALS tDIFF tEQTILDE tNOTTILDE tTILDE tPUSH tSHIFT tBAND tBOR tDEFINED
%token ELSE ELSIF FOR IN RESCUE ENSURE CLASS MODULE DEF tCOMMA tPOINT tDOUBLECOLON tCOLON THEN
%token tLBRACKET tRBRACKET NIL SELF tTHEN NUMERIC tPLUSASGN tMINUSASGN tMULASGN tDIVASGN
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
compstmt : stmt texpr opt_t;
texpr : /* empty */
      | texpr t expr;
opt_blockvar : /* empty */
            | '|' block_var '|';
opt_block : /* empty */
         | DO opt_blockvar compstmt END;
stmt : call DO opt_blockvar compstmt END
| UNDEF fname
| ALIAS fname fname
| stmt IF expr
| stmt WHILE expr
| stmt UNLESS expr
| stmt UNTIL expr
| 'BEGIN' '{' compstmt '}' /*object initializer*/
| 'END' '{' compstmt '}' /*object finalizer*/
| lhs = command opt_block
| expr
;
expr : mlhs = mrhs
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
 | primary.operation call_args
 | primary '::' operation call_args
 | SUPER call_args
;
paren_or_call_args : '(' ')'
              | '(' call_args ')';
opt_call_args : /* empty */
              | paren_or_call_args;
function : operation opt_call_args
        | primary '.' operation paren_or_call_args
        | primary '::' operation paren_or_call_args
        | primary.operation
        | primary '::' operation
        | SUPER paren_or_call_args
        | SUPER
;
arg : lhs = arg
| lhs op_asgn arg
| arg '..' arg | arg '...' arg
| arg '+' arg | arg '-' arg | arg '*' arg | arg '/' arg
| arg '%' arg | arg '**' arg
| '+' arg | '-' arg
| arg '|' arg
| arg '^' arg | arg '&' arg
| arg '<=>' arg
| arg '>' arg | arg '>=' arg | arg '<' arg | arg '<=' arg
| arg '==' arg | arg '===' arg | arg '!=' arg
| arg '=~' arg | arg '!~' arg
| '!' arg | '~' arg
| arg '<<' arg | arg '>>' arg
| arg '&&' arg | arg '||' arg
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
             | < identifier;
primary: '(' compstmt ')'
| literal
| variable
| primary '::' identifier
| '::' identifier
| primary '[' opt_args ']'
| '[' opt_args_comma ']'
| '{' opt_args_or_assocs '}'
| RETURN opt_call_args
| YIELD opt_call_args
| tDEFINED '(' arg ')'
| function
| function '{' opt_block_var compstmt '}'
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
| CLASS identifier opt_subclass
    compstmt
  END
| MODULE identifier
    compstmt
  END
| DEF fname argdecl
    compstmt
  END
| DEF singleton point_or_doublecolon fname argdecl
    compstmt
  END;
point_or_doublecolon : '.'
                     | '::';
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
               | mlhs_item_list ',' mlhsitem;
opt_mul_opt_lhs : /* empty */
                | '*' lhs
                | '*';
mlhs : mlhs_item_list opt_mul_opt_lhs
     | '*' lhs;
mlhs_item : lhs | '(' mlhs ')';
lhs : variable
    | primary '[' opt_args ']'
    | primary '.' identifier;
mrhs : args opt_comma_mul_arg
     | '*' arg;
opt_comma_assocs : /* empty */
                 | ',' assocs;
opt_comma_amp_arg : /* empty */
                  | ',' '&' arg;
call_args : args
          | args opt_comma_assocs opt_comma_mul_arg opt_comma_amp_arg
          | assocs opt_comma_mul_arg opt_comma_amp_arg
          | '*' arg opt_comma_amp_arg | '&' arg
          | command;
args : arg
     | args ',' arg;
argdecl : '(' arglist ')'
        | arglist t;
identifier_list : identifier
                | identifier_list ',' identifier;
opt_comma_mul_ident : /* empty */
                    | ',' '*'
                    | ',' '*' identifier;
opt_comma_amp_ident : /* empty */
                    | ',' '&'identifier;
opt_amp_ident : /* empty */
              | '&'identifier;
arglist : identifier_list opt_comma_mul_ident opt_comma_amp_ident
        | '*'identifier opt_comma_amp_ident
        | opt_amp_ident;
singleton : variable
        | '(' expr ')';
assocs : assoc
       | assocs ',' assoc;
assoc : arg '=>' arg;
variable : VARNAME
         | NIL
         | SELF;
literal : NUMERIC
        | SYMBOL
        | STRING
        | STRING2
        | HERE_DOC
        | REGEXP;
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
