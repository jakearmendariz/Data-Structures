#Makefile
#
#Assignment 3
#Jake Armendariz 1650932
#12B Bhatti
#Makefile-- creates an executable: BST
# contains a valgrind under check
# cleans
ADT_NAME = BST
SOURCES	 = BST.c	BSTClient.c
OBJECTS	 = BST.o	BSTClient.o
HEADERS	 = BST.h
EXEBIN	 = BST
FLAGS	 = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN)
