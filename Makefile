all: 1730ed

1730ed: main.o
	g++ -Wall -lmenu -lncurses -o 1730ed main.o

main.o: main.cpp methods_main.h methods1.h methods2.h methods3.h
	g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c -lmenu -lncurses main.cpp

clean:
	rm -f 1730ed
	rm -f main.o