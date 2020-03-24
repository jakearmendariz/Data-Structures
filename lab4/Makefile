#Makefile with a BlockChainClient executable
#Jake Armendariz 1650932
#12M Lab 4
ADT_NAME  = Block
SOURCES	  = Blockchain.c	BlockchainClient.c	Block.c
OBJECTS   = Blockchain.o	BlockchainClient.o	Block.o
HEADERS   = Blockchain.h	Block.h
EXEBIN    = BlockchainClient
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

