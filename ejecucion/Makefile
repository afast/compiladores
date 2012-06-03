all: test
	make stack.o
test: test.cpp stack.o base.o
	g++ test.cpp stack.o base.o -o test
stack.o:
	g++ stack.cpp base.h -c

base.o: base.cpp
	g++ base.cpp -c

clean:
	rm -f *.o
