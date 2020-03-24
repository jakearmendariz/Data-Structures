/**
 * BlockChain.c
 *
 * Jake Armendariz
 * 1650932
 * 12M
 *
 * This contains the methods to manipulate the blockchain
 * All it is an array of Blocks with a max size of 100
 * Once it excedes max size the program will delete the head
 *
 */
#include "Blockchain.h"
/**
 * BlockChain
 * A basic structure with a size variabl and a chain with max size 100
 */
typedef struct BlockchainObj{
        int size;
        Block chain[100];
} BlockchainObj;

Blockchain newBlockchain(){
	Blockchain bc = malloc(sizeof(Blockchain));
	bc->size = 0;
	return bc;
}

/**
 * freeBlockchain
 * If B is null an error will be printed
 * Deallocates each block using a forloop and then frees the chain when its done
 */
void freeBlockchain(Blockchain B){
	if(B == NULL){
		fprintf(stderr, "Error in Blockchain.c function freeBlockChain null chain\n");
		return;
	}
	for(int i = 0; i < B->size; i++){
		freeBlock(B->chain[i]);
	}
	free(B);
}


/**
 * append
 * If B is null an error will be printed
 * Adds a new Block to the chain
 * If size is 0 the hash value will be 0 otherwise iut will be the hash value before it
 */
int append(Blockchain B, char* data){
	
	if(B == NULL){
		fprintf(stderr, "Error in  Blockchain.c in function: append, NULL Blockchain");
		return 0;
	}
	
	if(B->size == 0){
		 Block a = newBlock(data, 0, 0);
		 B->chain[B->size] = a;
		 B->size++;
		// return B->size;
	}
	else{
		printf("Start\n");
		Block a = newBlock(data, B->size, hash(B->chain[B->size-1]));
		printf("Medium\n");
		B->chain[B->size] = a;
		printf("End\n");
		B->size++;
               // return B->size; 
	}	
	return B->size;
}

/**
 * size
 * returns the current number of Blocks in the chain
 */
int size(Blockchain B){
	if(B == NULL){
                fprintf(stderr, "Error in Blockchain.c, function: size, null Blockchain\n");
                return 0;
        }
	return B->size;
}

/**
 * get
 * If B is null an error will be printed
 * @return the block with the given id
 */
Block get(Blockchain B, int id){
	 if(B == NULL){
                fprintf(stderr, "Error in Blockchain.c, function: get(), null Blockchain\n");
                return NULL;
        }
	if(id < B->size){
		return B->chain[id];
	}	
	fprintf(stderr, "Error: could not find block of id: %d in method get", id);
	return NULL;
}


/**
 * valid
 * If B is null an error will be printed
 * if the hash value increases correctly a one will be returned otherwise a 0 will
 */
int valid(Blockchain B){
	 if(B == NULL){
                fprintf(stderr, "Error in Blockchain.c, function: valid, null Blockchain\n");
                return 0;
        }
	for(int i = 0; i < B->size; i++){
		if(previousHash(B->chain[i]) != hash(B->chain[i])-diffHash(B->chain[i])){
			return 0;
		}
	}
	return 1;
}

/**
 * removeLast
 * If B is null an error will be printed
 * Dealloactes the last block and lowers size by 1
 */
void removeLast(Blockchain B){
	 if(B == NULL){
                fprintf(stderr, "Error in Blockchain.c, function: removeLast, null Blockchain\n");
        	return;
	}   
	if(B->size ==0){
		fprintf(stderr, "Error the chain is empty");
		return;	
	}
	B->size--;
	freeBlock(B->chain[B->size]);
}

/**
 * printBlockchain
 * If B is null an error will be printed
 * prints the full chain to the out file
 */
void printBlockchain(FILE* out, Blockchain B){
	 if(B == NULL){
                fprintf(stderr, "Error in Blockchain.c, function: printBlockChain, null Blockchain\n");
         	return;
	}
	for(int i = 0; i < B->size; i++){
		printBlock(out, B->chain[i]);
	}
}
/**
 * Prints the contents of the block chain to the terminal so its easier for me to check my program
 */
void printChain(Blockchain B){
	printf("size:%d \n", B->size);
	for(int i = 0; i < B->size; i++){
		p(B->chain[i]);
	}
}
