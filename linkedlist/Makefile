#Jake Armendariz
#Makefile for checking leakage
#It also compiles list.c
#January 30, 2019
#12B
list: list.o
	gcc -o list list.o

list.o : list.c list.h
	gcc -c -std=c99 -Wall list.c

check : list.c
	valgrind --leak-check=full ./list

clean :
	rm -f list list.o

