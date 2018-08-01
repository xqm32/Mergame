#
#	Author: xqm32	Date: 25/7/18
#	File: ./makefile
#

main: main.cpp libmergame.a
	g++ -std=c++11 -o main main.cpp libmergame.a -lncurses

libmergame.a: mainfunc.o enterfunc.o printfunc.o
	ar -r libmergame.a mainfunc.o enterfunc.o printfunc.o sare.o

mainfunc.o enterfunc.o printfunc.o sare.o: lib/mainfunc.cpp lib/enterfunc.cpp lib/printfunc.cpp lib/sare.cpp
	g++ -std=c++11 -c lib/mainfunc.cpp lib/enterfunc.cpp lib/printfunc.cpp lib/sare.cpp -lncurses

.PHONY: clean lema clsa

clean:
	mv data/text.mso data/text.bak
	rm -f main mainfunc.o enterfunc.o printfunc.o sare.o libmergame.a data/.first_play data/*.msa data/*.mso
	mv data/text.bak data/text.mso

lema:
	mv data/text.mso data/text.bak
	rm -f mainfunc.o enterfunc.o printfunc.o sare.o libmergame.a data/.first_play data/*.msa data/*.mso
	mv data/text.bak data/text.mso

clsa:
	mv data/text.mso data/text.bak
	rm -f data/.first_play data/*.msa data/*.mso
	mv data/text.bak data/text.mso