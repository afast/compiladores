CC = g++

CFLAGS= -lfl -std=c++0x

BFLAGS= -yd

PROGRAM = myruby

all: main

main: y.tab.c lex.yy.c
	cd ejecucion; make
	$(CC) -o $(PROGRAM) y.tab.c lex.yy.c $(CFLAGS) ejecucion/stack.o ejecucion/base.o ejecucion/RObject.o ejecucion/RString.o ejecucion/RInteger.o ejecucion/RBool.o ejecucion/Util.o

y.tab.c: gramatica.y
	bison $(BFLAGS) gramatica.y

y.tab.h: y.tab.c

lex.yy.c: ruby_lex.l
	flex ruby_lex.l


clean:
	cd ejecucion; make clean
	rm -f $(PROGRAM) lex.yy.c y.tab.c y.tab.h
