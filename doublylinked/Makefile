#A Makefile for the programs
#Jake Armendariz 1650932 12B Assignment 2 Febuary 7, 2019
#I wasn't sure if I should remove the main file or not but I chose to keep it because I assume you are testing with your own main.c file
listTest: list.o main.o listUtil.o
	gcc -o listTest list.o main.o listUtil.o

listUtil.o: listUtil.c listUtil.h
	gcc -c -std=c99 -Wall listUtil.c

list.o: list.c list.h
	gcc -c -std=c99 -Wall list.c

main.o: main.c list.h
	gcc -c -std=c99 -Wall main.c

clean:
	rm -f listTest main.o list.o listUtil.o

check:
	valgrind --leak-check=full listTest
