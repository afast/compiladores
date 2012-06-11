all: test robject rstring rinteger rclass rbool rarray
	make stack.o robject rstring rinteger rclass rbool rarray
test: test.cpp stack.o base.o robject rstring rinteger rclass rbool rarray
	g++ test.cpp stack.o base.o RObject.o RString.o RInteger.o RClass.o RBool.o RArray.o -o test -std=gnu++0x
stack.o: stack.cpp stack.h base.o
	g++ stack.cpp base.h -c -std=gnu++0x
base.o: base.cpp base.h
	g++ base.cpp -c -std=gnu++0x

robject: RObject.h RObject.cpp
	g++ RObject.cpp -c
rstring: RString.h RString.cpp
	g++ RString.cpp -c
rinteger: RInteger.h RInteger.cpp
	g++ RInteger.cpp -c
rclass: RClass.h RClass.cpp
	g++ RClass.cpp -c -std=c++0x
rbool: RBool.h RBool.cpp
	g++ RBool.cpp -c
rarray: RArray.h RArray.cpp
	g++ RArray.cpp -c

clean:
	rm -f *.o
