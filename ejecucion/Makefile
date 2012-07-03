CFLAGS= -g -O0

pruebawhile: pruebawhile.cpp all
	g++ pruebawhile.cpp stack.o RObject.o RString.o RInteger.o RClass.o RBool.o Util.o base.o memory.o RArray.o  -std=c++0x $(CFLAGS) -o while
pruebaif: pruebaif.cpp all
	g++ pruebaif.cpp stack.o RObject.o RString.o RInteger.o RClass.o RBool.o Util.o base.o memory.o RArray.o  -std=c++0x $(CFLAGS) -o if
all: RObject.o RString.o RNumeric.o RInteger.o RClass.o RBool.o RArray.o RVariable.o memory.o RDecimal.o stack.o RCommand.o

stack.o: stack.cpp stack.h base.o
	g++ stack.cpp base.h -c -std=gnu++0x $(CFLAGS)
base.o: base.cpp base.h
	g++ base.cpp -c -std=gnu++0x $(CFLAGS)

RObject.o: RObject.h RObject.cpp
	g++ RObject.cpp -c $(CFLAGS)
RString.o: RString.h RString.cpp
	g++ RString.cpp -c $(CFLAGS)
RCommand.o: RCommand.h RCommand.cpp
	g++ RCommand.cpp -c $(CFLAGS)
RInteger.o: RInteger.h RInteger.cpp
	g++ RInteger.cpp -c $(CFLAGS)
RDecimal.o: RDecimal.h RDecimal.cpp
	g++ RDecimal.cpp -c $(CFLAGS)
RNumeric.o: RNumeric.h RNumeric.cpp
	g++ RNumeric.cpp -c $(CFLAGS)
RClass.o: RClass.h RClass.cpp
	g++ RClass.cpp -c -std=c++0x $(CFLAGS)
RBool.o: RBool.h RBool.cpp
	g++ RBool.cpp -c $(CFLAGS)
RArray.o: RArray.h RArray.cpp
	g++ RArray.cpp -c $(CFLAGS)
RVariable.o: RVariable.h RVariable.cpp
	g++ RVariable.cpp -c $(CFLAGS)
util: Util.h Util.cpp
	g++ Util.cpp -c $(CFLAGS)
memory.o: memory.h memory.cpp
	g++ memory.cpp -c $(CFLAGS) -std=c++0x 
clean:
	rm -f *.o *.gch *.orig
