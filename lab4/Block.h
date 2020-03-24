/**
 * Block.h
 *
 * Jake Armendariz
 * 1650932
 * 12M, lab4 
 * Header file for a block
 *
 * THis just has some simple mehod headers and definitions for creating a basic linked list
 */
#include <stdio.h>
#include <stdlib.h>
#ifndef _BLOCK_H_INCLUDE_
#define _BLOCK_H_INCLUDE_
/**
 * structure initalizgation for a Block
 * Will have an id, data and prevHash values
 */
typedef struct BlockObj* Block;

/*
 * newBlock
 * Creates and mallocs a new block
 * @param data is a string assigning the block
 * @param id represents position on the Blockchain
 * @param hash is the previous hash value
 */
Block newBlock(char* data, int id, long hash);

/**
 * freeBlock
 * frees the block and the data string
 */
void freeBlock(Block B);


/**
 * data
 *@returns a pointer to the blocks data
 */
char* data(Block B);

/**
 * previousHash
 * @returns the previousHash value stored ina  varible
 */
long previousHash(Block B);

/*
 * hash
 * @returns the current hash == the previousHash + strlen(data) + id
 */ 
long hash(Block B);

/**
 * printBlock
 * Prints the data to the file
 */
void printBlock(FILE* out, Block B);
//This was jut a printer method for me
void p(Block B);

//Its the combination of the id and data length
long diffHash(Block B);

#endif


