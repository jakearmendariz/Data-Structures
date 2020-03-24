/**
 * BST.h
 *
 * Jake Armendariz
 * 1650932
 * 12B
 *
 * Header file for BST.c
 * Contains headers methods for manipulating and traversing a binary search tree
 * Has the BSTOBJ dfined here
 */


#include <stdio.h>
#include <stdlib.h>
#ifndef _BST_H_INCLUDE_
#define _BST_H_INCLUDE_
#define TRUE 1
#define FALSE 0
#define _POSIX_SOURCEE

//Tree node to store strings, space still needs to be allocated for strings
//This node will be part of the binary tree
typedef struct BSTObj {
    char               *term;           /* string data in each block */
//    int term;
    struct BSTObj      *leftChild;      /* ptr to left child */
    struct BSTObj      *rightChild;     /* ptr to right child */
} BSTObj;

//Adds a new node to the tree, space must be allocated in the BST node
//returns a -1 if it cannot insert and 0 if not
int insert(char *new_data, BSTObj **pBST);

//inorderTraverse
//prints out the traversal in order
void inorderTraverse(FILE *out, BSTObj *T);

//preorderTraverse
// print to OUT the preorder traversal
void preorderTraverse(FILE *out,BSTObj *T);

//postOrderTraverse
// print to OUT the postorder traversal
void postorderTraverse(FILE *out,BSTObj *T);

//inorderLeaves
//T is the root head
// print the leaves of the tree in inorder to OUT
void inorderLeaves(FILE *out, BSTObj *T);

//term_to_find is the node we need to find
// return the node with the term case insensitive matching item_to_find, NULL if not found
BSTObj *find(char *term_to_find, BSTObj *T);

//@param T is the root
//@param height = 0
//Returns height of tree (heigh = -1), its just a root
int treeHeight(BSTObj *T, int height);

//Copies the tree and returns a new memory independent copy of the tree
//Returns a list head
BSTObj * copyTree(BSTObj *T);

//Removes node from tree and dealocates
void makeEmpty(BSTObj **pT);

#endif
