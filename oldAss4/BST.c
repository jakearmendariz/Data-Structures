/**
 * BST.c
 *
 * Jake Armendariz
 * 1650932
 * 12B
 *
 * Assignment 4
 * 
 *Contains functions to build, delete and print the BST
 * Uses BST for its nodes and function headers
 * Suppose to handle ever type of input
 * Can insert nodes, free the tree, find nodes and print the tree in any order, print leaves and copy a memory independent tree
 * All methods are handeled in BSTClient.c 
 */
#include "BST.h"
#include <string.h>
#include <strings.h>

/**
 * insert
 *
 * Deals with null pointers with a error message
 * inserts the given data into the binary search tree
 * if the tree is empty it will become the root
 * Otherwise it will recursivly move down tree to where it fits
 * If pBST is null an error message will be printed out
 * if duplicate it will tell as well
 */
int insert(char *new_data, BSTObj **pBST)
{
	BSTObj *head = *pBST;
	if (pBST == NULL)
	{
		fprintf(stderr, "Error, null pointer to the pointer to list head\n");
		return -1;
	}

	if (new_data == NULL)
	{
		fprintf(stderr, "Error, null new datad\n");
		return -1;
	}

	//Empty list, adds root node
	if (*pBST == NULL)
	{
		BSTObj *a = malloc(sizeof(BSTObj));
		a->term = malloc(150);
		strcpy(a->term, new_data);
		*pBST = a;
		return 0;
	}
	else if (strcasecmp(head->term, new_data) > 0)
	{
		if (head->leftChild == NULL)
		{
			BSTObj *a = malloc(sizeof(BSTObj));
			a->term = malloc(150);
			strcpy(a->term, new_data);
			;
			head->leftChild = a;
			return 0;
		}
		else
		{
			return insert(new_data, &(head->leftChild));
		}
	}
	else if (strcasecmp(head->term, new_data) < 0)
	{
		if (head->rightChild == NULL)
		{
			BSTObj *a = malloc(sizeof(BSTObj));
			a->term = malloc(150);
			strcpy(a->term, new_data);
			head->rightChild = a;
			return 0;
		}
		else
		{
			return insert(new_data, &(head->rightChild));
		}
	}
	else
	{
		//		printf("Duplicate string \"%s\"\n", new_data);
		return -1;
	}
}

/**
 * inorderTraverse
 *
 * traverses in order
 * It recursivly call the left, print, outside
 */
void inorderTraverse(FILE *out, BSTObj *T)
{
	///fopen(out, "w");
	if (T == NULL)
	{
		return;
	}

	inorderTraverse(out, T->leftChild);
	fprintf(out, "%s\n", T->term);
	inorderTraverse(out, T->rightChild);
	//fclose(out);
}

/**
 * preorderTraverse
 *
 * prints the node in preorder
 * recursivly prints node, then its left, then right
 */
void preorderTraverse(FILE *out, BSTObj *T)
{
	if (T == NULL)
	{
		return;
	}
	fprintf(out, "%s\n", T->term);
	preorderTraverse(out, T->leftChild);
	preorderTraverse(out, T->rightChild);
}

/**
 * postorderTraverse
 *
 * prints in postOrder
 * recursivly goes down left then right then prints (bottoms nodes first)
 */
void postorderTraverse(FILE *out, BSTObj *T)
{
	if (T == NULL)
	{
		return;
	}
	postorderTraverse(out, T->leftChild);
	postorderTraverse(out, T->rightChild);
	fprintf(out, "%s\n", T->term);
}

/**
 * inorderLeaves
 *
 * prints the leaves in order from smallest to greatest
 */
void inorderLeaves(FILE *out, BSTObj *T)
{
	if (T == NULL)
	{
		return;
	}

	inorderLeaves(out, T->leftChild);

	if (T->leftChild == NULL)
	{
		if (T->rightChild == NULL)
		{
			printf("%s\n", T->term);
		}
	}
	inorderLeaves(out, T->rightChild);
}

/**
 * find
 * 
 * Finds the node with term_to_find as it's value
 * if its not there an error message will be returned
 * finds the term recursively by moving down the BST
 * the best case is log(n) as it's a binary search
 * returns the term that is found
 */
BSTObj *find(char *term_to_find, BSTObj *T)
{
	//printf("Searching node: %d\n", T->term);
	if (T == NULL)
	{
		return NULL;
	}
	if (term_to_find == NULL)
	{
		fprintf(stderr, "Error in find function, null string");
		return NULL;
	}
	int diff = strcasecmp(T->term, term_to_find);
	if (diff == 0)
	{
		return T;
	}
	else if (diff < 0)
	{
		return find(term_to_find, T->rightChild);
	}
	else
	{
		return find(term_to_find, T->leftChild);
	}
}

/**
 * treeHeight
 *
 * compute the height of the tree
 * Recrusivly adds one everytime it moves down a level until it is at the bottom
 * @returns tree height, 0 if empty
 */
int treeHeight(BSTObj *T, int height)
{
	if (T == NULL)
	{
		return height;
	}
	int leftDepth = treeHeight(T->leftChild, height + 1);
	int rightDepth = treeHeight(T->rightChild, height + 1);
	if (leftDepth > rightDepth)
	{
		return leftDepth;
	}
	else
	{
		return rightDepth;
	}
}

/**
 * copyTree
 *
 * if null tree null is returned
 * @returns a complete and memory independing version
 */
BSTObj *copyTree(BSTObj *T)
{
	if (T == NULL)
	{
		return NULL;
	}
	BSTObj *root = malloc(sizeof(BSTObj));
	root->term = (char *)malloc(150);
	strcpy(root->term, T->term);
	root->leftChild = copyTree(T->leftChild);
	root->rightChild = copyTree(T->rightChild);
	return root;
}

/**
 * makeEmpty
 *
 * Does not free the pT
 * Deletes all the nodes
 * removes all nodes from tree and deallocates space
 */
void makeEmpty(BSTObj **pT)
{
	if (pT == NULL)
	{
		fprintf(stderr, "Error in makeEmpty function null poinyter to the pointer to list head");
		return;
	}
	if (*pT == NULL)
	{
		return;
	}
	makeEmpty(&((*pT)->leftChild));
	makeEmpty(&((*pT)->rightChild));
	free((*pT)->term);
	free(*pT);
}

//Calls the other methids to delete
int deleteItem(char *term_to_delete, BSTObj **pT)
{
	return 0;
}

//Actually frees the node
void deleteNode(BSTObj *T)
{
	free(T);
}

//retrieveNode
//T is a dummy pointer with a child of the list head so that it may work
//Both of T's children will be the root
//Based on the sizes it will move right and left. once the child's equal to the node
//To be found, it will return the parent node
//@returns the parent node to the term that needs to be deleted
BSTObj *retrieveNode(char *term_to_find, BSTObj *T)
{
	if (T == NULL)
	{
		return NULL;
	}
	int diff = strcasecmp(T->term, term_to_find);
	if (diff < 0)
	{
		if (strcasecmp(T->rightChild->term, term_to_find) == 0)
		{
			return T;
		}
		return find(term_to_find, T->rightChild);
	}
	else if (diff > 0)
	{
		if (strcasecmp(T->leftChild->term, term_to_find) == 0)
		{
			return T;
		}
		return find(term_to_find, T->leftChild);
	}
	else
	{
		printf("Error in the retrieve node function, equaivalent nodes\n");
		return NULL;
	}
}

//Returns the leftmost element
BSTObj *findLeftMost(BSTObj *root)
{
	if (root->leftChild == NULL && root->rightChild == NULL)
	{
		return root;
	}

	return findLeftMost(root->leftChild);
}
