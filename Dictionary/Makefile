
ADT_NAME  = Dictionary
SOURCES   = Dictionary.c	DictionaryClient2.c
OBJECTS   = Dictionary.o	DictionaryClient2.o
HEADERS   = Dictionary.h
EXEBIN    = DictionaryTest
FLAGS	  = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN)

