CC = g++

CFLAGS= -lfl -std=c++0x

BFLAGS= -yd

PROGRAM = myruby

all: main

gramatica: y.tab.c lex.yy.c generador.o ast.o
	$(CC) -o $(PROGRAM) y.tab.c lex.yy.c $(CFLAGS) ejecucion/stack.o ejecucion/base.o ejecucion/RObject.o ejecucion/RString.o ejecucion/RInteger.o ejecucion/RBool.o ejecucion/memory.o ejecucion/RArray.o ejecucion/RClass.o generador.o ast.o ejecucion/RNumeric.o ejecucion/RDecimal.o

ejecucion:
	cd ejecucion; make all
main: y.tab.c lex.yy.c generador.o ast.o
	cd ejecucion; make all
	$(CC) -o $(PROGRAM) y.tab.c lex.yy.c $(CFLAGS) ejecucion/stack.o ejecucion/base.o ejecucion/RObject.o ejecucion/RString.o ejecucion/RInteger.o ejecucion/RBool.o ejecucion/memory.o ejecucion/RArray.o ejecucion/RClass.o generador.o ast.o ejecucion/RNumeric.o ejecucion/RDecimal.o

generador.o: generador.h generador.cpp
	g++ generador.cpp -c -std=c++0x
ast.o: ast.h ast.cpp
	g++ ast.cpp -c
y.tab.c: gramatica.y
	bison $(BFLAGS) gramatica.y

y.tab.h: y.tab.c

lex.yy.c: ruby_lex.l
	flex ruby_lex.l


clean:
	cd ejecucion; make clean
	rm -f $(PROGRAM) lex.yy.c y.tab.c y.tab.h
