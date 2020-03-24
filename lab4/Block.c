/**
 * Jake Armendariz
 * 1650932
 * lab4
 * Block.c
 *
 * Description:
 * Contains the block manipulation method
 * Can add blocks, remove them and access the data they hold
 */
#include "Block.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct BlockObj{
	int id;
	long prevHash;
	char *data;
	
}BlockObj;
/**
 * newBlock
 * Sets all of the data
 * @returns the intialized Block
 */
Block newBlock(char* data, int id, long hash){
	Block a = malloc(sizeof(Block));
	a->id = id;
	a->data = malloc(100);
	strcpy(a->data, data);
	a->prevHash = hash;
	return a;
}

/**
 * freeBlock
 * Frees the data because it is the only part allocated
 */
void freeBlock(Block B){
	if(B == NULL){
		fprintf(stderr, " Error in free Block, Block is null\n");
		return;
	}
	free(B->data);
	free(B);
}

/**
 * data
 * Returns the data of the block given
 * If Null block and error mesage will be printed
 */
char* data(Block B){
	 if(B == NULL){
                fprintf(stderr, " Error in Block.c data(Block B), Block is null\n");
        	return NULL;
	}
	return B->data;
}

/**
 * previousHash
 * If B is null an error will be printed
 * The current sum is the previous hash value + chars in data + id
 * Subtracting the chars and id we get the value of the previous has
 */
long previousHash(Block B){
	 if(B == NULL){
                fprintf(stderr, " Error in Block.c previousHash(Block B), Block is null\n");
        	return 0;
	}
	long a = B->prevHash;
	return a;
}

/**
 * diffHash
 * If B is null an error will be printed
 * @return what is added onto the block to make checking easier in future blocks and methods
 */
long diffHash(Block B){
	 if(B == NULL){
                fprintf(stderr, " Error in Block.c diffHash(Block B), Block is null\n");
        	return 0;
	}
	long sum = B->id;
	sum += strlen(B->data);
	return sum;
}

/**
 * hash
 * If B is null an error will be printed
 * @return the prev hash + id + strlen(data);
 */
long hash(Block B){
	 if(B == NULL){
                fprintf(stderr, " Error in Block.c hash(Block B), Block is null\n");
        	return  0;
	}
	long a = B->prevHash + diffHash(B);
	return a;
}

/**
 * Prints Block's data to a print file
 */
void printBlock(FILE* out, Block B){
	 if(B == NULL){
                fprintf(stderr, " Error in Block.c printBlock(File* out, Block B), Block is null\n");
       		return;
	 }
	fprintf(out, "%d:%s\n", B->id, B->data); 
}

void p(Block B){
        printf("Block %d, data: %s, and prev hash: %ld current hash:%ld\n\n", B->id, B->data, B->prevHash, hash(B));
}
