#This make file creates an executable binary file called charType and includes a clean utility
#Jake Armendariz, 1650932, January 25, 2019
charType : charType.o
	gcc -o charType charType.o

charType.o : charType.c
	gcc -c -std=c99 -Wall charType.c

check : charType.c
	valgrind --leak-check=full charType charType out

clean :
	rm -f charType charType.o
