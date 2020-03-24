/**
 *Jake Armendariz
 *1650932
 *Assignment 2, 12B
 *Febuary 7, 2019
 *
 * Description:
 * Contains the printing and reversal method used to debug code
 * Can print linked list and nodes in both directions
 */

#include "listUtil.h"
//#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints the full linked list
 * Uses the printNode method so it will tell the contents of the current nodes value and the previous and post nodes as well
 */
void printNodeList(Node *list_head)
{
	Node *curr = list_head;
	int counter = 0;
	//Repeats until completes list
	while (curr != NULL && counter < 20)
	{
		printNode(curr);
		curr = curr->next;
		counter++;
	}
	printf("\n");
}

/**
 * Prints an individual node
 * Will print its contents and its previous and following node as well
 * If it is at the front or back of list it will tell that it is NULL
 */
void printNode(Node *a)
{
	//	printf("In printNode\n");
	if (a->next != NULL && a->prev != NULL)
	{
		printf("The value is: %d. It's previous node is: %d. It's next node is: %d\n", a->value, a->prev->value, a->next->value);
	}
	else if (a->prev != NULL)
	{
		printf("The value is: %d. It's previous node is: %d. It's next node is: NULL\n", a->value, a->prev->value);
	}
	else if (a->next != NULL)
	{
		printf("The value is: %d. It's previous node is: NULL It's next node is: %d\n", a->value, a->next->value);
	}
	else
	{
		printf("The value is: %d. It's previous node is: NULL It's next node is: NULL\n", a->value);
	}
	//	printf("Printed null values");
}
