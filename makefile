#
#	Author: xqm32	Date: 25/7/18
#	File: ./makefile
#

main: main.cpp libmergame.a lib/mergame.h
	g++ -std=c++11 -o main main.cpp libmergame.a -lncurses

libmergame.a: mainfunc.o enterfunc.o printfunc.o
	ar -r libmergame.a mainfunc.o enterfunc.o printfunc.o

mainfunc.o enterfunc.o printfunc.o: lib/mainfunc.cpp lib/enterfunc.cpp lib/printfunc.cpp lib/mergame.h
	g++ -std=c++11 -c lib/mainfunc.cpp lib/enterfunc.cpp lib/printfunc.cpp -lncurses

.PHONY: clean

clean:
	rm -f main mainfunc.o enterfunc.o printfunc.o libmergame.a data/.first_play