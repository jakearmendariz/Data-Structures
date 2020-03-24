/**
 * Blockchain.h
 *
 * Jake Armendariz
 * 1650932
 * 12M
 *
 * lab4
 *
 * Description
 * Edits an array of Block pointers, it can add, remove, search and free the blocks
 * Main purpose is pretty simple,the methods just help
 */

#ifndef _BLOCKCHAIN_H_INCLUDE_
#define _BLOCKCHAIN_H_INCLUDE_

#include "Block.h"
/**
 * BlockChain
 * The Object is created as a pointer so it may be modified
 * contains chain, an array of Blocks and size, the current size of the array
 */
typedef struct BlockchainObj* Blockchain;


/**
 * newBlockChain
 * Allocates memory for the new chain
 * @returns the Blockchain
 */
Blockchain newBlockchain();

/**
 * freeBlockChain
 * Deallocates memory for the whole chain and each block inside
 */
void freeBlockchain(Blockchain B);

/**
 * append
 * Adds a new block to the chain
 * Sets the id to the place in chain
 */
int append(Blockchain B, char* data);

/**
 * size
 * @returns the size of the chain
 */
int size(Blockchain B);

/**
 * get
 * returns the block with the given id
 */
Block get(Blockchain B, int idx);

/**
 * valid
 * @returns 1 if the hash is valid
 * @returns 0 if it is not valid
 */
int valid(Blockchain B);

/**
 * removeLast
 * removes the last blocka and deallocate's its memory
 */
void removeLast(Blockchain B);

/**
 * printBlockchain
 * prirns the id and data to the output file
 */
void printBlockchain(FILE* out, Blockchain B);

//Prints blockchain to the console window
void printChain(Blockchain B);

#endif





