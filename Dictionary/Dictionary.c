/**
 * Dictionary.c
 * 
 * Jake Armendariz
 * 1650932
 * 12B
 * Assignment5
 * 
 * Contains all pf the methods to traverse the hash methods
 * Can add elements, remove them ane all the other fun stuff
 * Hash function was provided
 */

#include <stdio.h>
#include "Dictionary.h"
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift)
{
    int sizeInBits = 8 * sizeof(unsigned int);
    shift = shift & (sizeInBits - 1);
    if (shift == 0)
        return value;
    return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char *input)
{
    unsigned int result = 0xBAE86554;
    while (*input)
    {
        result ^= *input++;
        result = rotate_left(result, 5);
    }
    //printf("%x\n", result);
    return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char *key, int tableSize)
{
    //printf("%x\n", pre_hash(key) % tableSize);
    if (key == NULL)
    {
        fprintf(stderr, "Error in hash function: null key\n");
    }
    return pre_hash(key) % tableSize;
}

/**
 * elementHead
 * 
 * @param H is the hash table
 * @param pos is the hash it is located in
 * @returns the elment at that point in the array
 */
bucketListObj *elementHead(HashTableObj *H, int pos)
{
    pos = pos % H->size;
    ;
    return H->bucket[pos];
}

/**
 * newHashTable
 * 
 * @param size
 * is the size of the array that the new hash table
 * it will store value inside of this size in an open ended hash
 * @return the new HashTableObj
 */
HashTableObj *newHashTable(int size)
{
    if (size < 0)
    {
        fprintf(stderr, "Error in newHashTable, size must be non-negative\n");
        return NULL;
    }
    // error checking code omitted
    // we explicitly allocate space for the fixed size element in HashTableObj, // the size element plus the space for the variable size array
    HashTableObj *H;
    H = (HashTableObj *)malloc(sizeof(HashTableObj) + sizeof(bucketList) * size);
    if (H == NULL)
    {
        fprintf(stderr, "Error in newHaHTable function, memory did not allocate");
    }
    H->size = size;
    for (int i = 0; i < size; i++)
    {
        H->bucket[i] = NULL;
    }
    return H;
}

/**
 * deleteHashTable
 * @param H is the hashtable to be deleted
 * deallocates all the space
 */
void deleteHashTable(HashTableObj *H)
{
    for (int i = 0; i < H->size; i++)
    {
        while (elementHead(H, i) != NULL)
        {
            bucketList a = elementHead(H, i);
            H->bucket[i] = a->next;
            free(a);
            a = NULL;
        }
    }
	free(H);
    H = NULL;
}

/**
 * member
 * 
 * @param H is the hastable
 * @param str is the string to find
 * if null pointers an error will be printed out
 * @returns 1 if found, 0 if string is not found
 */
int member(HashTableObj *H, char *str)
{
    if (H == NULL)
    {
        fprintf(stderr, "Error in member function: Null HashTable\n");
        return 0;
    }
    if (str == NULL)
    {
        fprintf(stderr, "Error in member function: Null String\n");
        return 0;
    }
    int n = hash(str, H->size);
    bucketList a = H->bucket[n];
    while (a != NULL && strcmp(a->item, str) != 0)
    {
        a = a->next;
    }
    if (a == NULL)
    {
        return 0;
    }
    if (strcmp(a->item, str) == 0)
    {
        return 1;
    }
    return 0;
}

/**
 * insert
 * 
 * @param H is the hash table
 * @param str is the string to be added
 * Based on the hash value it will add into the list
 */
void insert(HashTableObj *H, char *str)
{
    if (H == NULL)
    {
        fprintf(stderr, "Error in insert method: Null HashTable\n");
        return;
    }
    if (str == NULL)
    {
        fprintf(stderr, "Error in insert method: Null String\n");
        return;
    }
    
    int h = hash(str, H->size);
    bucketListObj *bl = malloc(sizeof(bucketListObj) + strlen(str) + 1);
    strcpy(bl->item, str);
    bl->next = elementHead(H, h);
    H->bucket[h] = bl;
}

/**
 * delete
 * 
 * @param H is the hashTabke
 * @param str is the string of the node to be deleted
 * deallocates the memory of the  nod eto be deleted
 * @returns 0 if error and 1 if found and deleted
 */
int delete (HashTableObj *H, char *str)
{
    if (H == NULL)
    {
        fprintf(stderr, "Error in delete function: Null HashTable\n");
        return 0;
    }
    if (str == NULL)
    {
        fprintf(stderr, "Error in delete function: Null String\n");
        return 0;
    }
    if (member(H, str) == 0)
    {
        return 0;
    }
    //Gets the size it would be in and then based on where it is in linked list deletes it
    int n = hash(str, H->size);
    bucketList a = H->bucket[n];
    bucketList b = a;
    bucketList c = a;
    while (a != NULL && strcmp(a->item, str) != 0)
    {
        c = a;
        a = a->next;
    }
    if (a == b)
    {
        H->bucket[n] = a->next;
        free(a);
        return 1;
    }
    else
    {
        c->next = a->next;
        free(a);
        return 1;
    }

    return 0;
}

/**
 * printHashTable
 * 
 * @param out is the file to which it will be printed
 * prints Bucket by bucket through the list
 */
void printHashTable(FILE *out, HashTableObj *H)
{
    if (H == NULL)
    {
        fprintf(stderr, "Error in printHashTable function: Null HashTable\n");
        return;
    }
    if (out == NULL)
    {
        fprintf(stderr, "Error in printHashTable function: Null out\n");
        return;
    }
    fprintf(out, "Hash table contents\n");
    for (int i = 0; i < H->size; i++)
    {
        //Seperates out by buckets
        fprintf(out, "bucket %d\n", i);
        bucketListObj *bl = H->bucket[i];
        while (bl != NULL)
        {
            fprintf(out, "    bucket list item = %s\n", bl->item);
            bl = bl->next;
        }
    }
}

