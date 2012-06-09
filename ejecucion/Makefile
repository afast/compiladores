all: test
	make stack.o
test: test.cpp stack.o base.o
	g++ test.cpp stack.o base.o -o test -std=gnu++0x
stack.o: stack.cpp stack.h base.o
	g++ stack.cpp base.h -c -std=gnu++0x

base.o: base.cpp base.h
	g++ base.cpp -c -std=gnu++0x

clean:
	rm -f *.o
