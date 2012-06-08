CC = gcc

CFLAGS= -lfl

BFLAGS= -yd

PROGRAM = ruby

all: main

main: y.tab.c lex.yy.c
	$(CC) -o $(PROGRAM) y.tab.c lex.yy.c $(CFLAGS)

y.tab.c: gramatica.y
	bison $(BFLAGS) gramatica.y

y.tab.h: y.tab.c

lex.yy.c: ruby_lex.l
	flex ruby_lex.l


clean:
	rm -f $(PROGRAM) lex.yy.c y.tab.c y.tab.h
