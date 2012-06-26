CFLAGS= -g -O0

pruebawhile: pruebawhile.cpp all
	g++ pruebawhile.cpp stack.o RObject.o RString.o RInteger.o RClass.o RBool.o Util.o base.o memory.o RArray.o  -std=c++0x $(CFLAGS) -o while
pruebaif: pruebaif.cpp all
	g++ pruebaif.cpp stack.o RObject.o RString.o RInteger.o RClass.o RBool.o Util.o base.o memory.o RArray.o  -std=c++0x $(CFLAGS) -o if
all: robject rstring rnumeric rinteger rclass rbool rarray memory rdecimal util stack.o

stack.o: stack.cpp stack.h base.o
	g++ stack.cpp base.h -c -std=gnu++0x $(CFLAGS)
base.o: base.cpp base.h
	g++ base.cpp -c -std=gnu++0x $(CFLAGS)

robject: RObject.h RObject.cpp
	g++ RObject.cpp -c $(CFLAGS)
rstring: RString.h RString.cpp
	g++ RString.cpp -c $(CFLAGS)
rinteger: RInteger.h RInteger.cpp
	g++ RInteger.cpp -c $(CFLAGS)
rdecimal: RDecimal.h RDecimal.cpp
	g++ RDecimal.cpp -c $(CFLAGS)
rnumeric: RNumeric.h RNumeric.cpp
	g++ RNumeric.cpp -c $(CFLAGS)
rclass: RClass.h RClass.cpp
	g++ RClass.cpp -c -std=c++0x $(CFLAGS)
rbool: RBool.h RBool.cpp
	g++ RBool.cpp -c $(CFLAGS)
rarray: RArray.h RArray.cpp
	g++ RArray.cpp -c $(CFLAGS)
util: Util.h Util.cpp
	g++ Util.cpp -c $(CFLAGS)
memory: memory.h memory.cpp
	g++ memory.cpp -c $(CFLAGS) -std=c++0x 
clean:
	rm -f *.o *.gch *.orig
