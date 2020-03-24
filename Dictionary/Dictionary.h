//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for the HashTable ADT
// Array implmentation with  bucket heads that point to linked list of items
// that hash to this bucket
//
// Note that the hash table size is decided by the client and passed to
// the new function that creates the hash table.
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_

typedef struct bucketListObj *bucketList;

typedef struct bucketListObj
{
    bucketList next;
    char item[];
} bucketListObj;

// this item will be dynamically allocated newHash,
// must manage the index to stay in allocated array range
typedef struct HashTableObj
{
    int size; // MUST COME FIRST!!!
    bucketList bucket[];
} HashTableObj;

//int hash(char *key, int tableSize);
HashTableObj *newHashTable(int size);
void deleteHashTable(HashTableObj *H);
int member(HashTableObj *H, char *str);
void insert(HashTableObj *H, char *str);
int delete (HashTableObj *H, char *str);
void printHashTable(FILE *out, HashTableObj *H);
#endif
