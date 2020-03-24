#-----------------------
#Makefile for lab2, creates an executeable binary file called FileReverse and includes a# clean utility
#-------------------------

FLAGS	= -std=c99 -Wall
SOURCES	= FileReverse.c
OBJECTS = FileReverse.o
EXEBIN	= FileReverse

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)
