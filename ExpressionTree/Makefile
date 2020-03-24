#Makefile
#Jake Armendariz
#12B
#lab5
ADT_NAME  =  ExpTree
ADT_DEPENDENCIES = Stack
SOURCES   = Stack.c  ExpTreeClient.c	ExpTree.c
OBJECTS   = Stack.o  ExpTreeClient.o	ExpTree.o
HEADERS   = ExpTree.h  Stack.h
EXEBIN    = PFC
FLAGS     = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 

