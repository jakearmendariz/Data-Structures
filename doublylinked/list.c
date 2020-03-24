/**
 * Jake Armendaroz
 * 12B
 * Assignment 2
 * 1650932
 * Febuary 7, 2019
 * list.c
 *
 * Description:
 * Contains a doubly linked list manipulation routines
 * Can create new nodes, insert nodes to the list at the end of based off of values
 * Can delete singular nodes or the entire list
 */
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @param id is the id of the new node
 * Allocates memory for the new node and returns null if memory allocation fails
 * @returns a new Node
 */
Node *create_new_node(int id)
{
	Node *a = malloc(sizeof(Node));
	a->value = id;
	if (a == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value\n");
		return NULL;
	}
	a->next = NULL;
	a->prev = NULL;
	return a;
}

/**
 * @param list head is the head or top of a list
 * @param to_be_inserted is the ptr that will go at the tail end of the list
 * Takes the to_be_inserted and sends it the end of the list. Changes the nearby pointers to make it easier
 * Using my getTail method to find the end of list
 * If a null ptr is given the function will print out an error message and terminate
 * post_condition, the list will be inserted
 */
void insert(Node **list_head, Node *to_be_inserted)
{
	if ((list_head) == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value, list head\n");
		return;
	}
	if (to_be_inserted == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value\n");
		return;
	}
	//Insetion bceomes the entire list
	if (*list_head == NULL)
	{
		*list_head = to_be_inserted;
		to_be_inserted->prev = NULL;
		to_be_inserted->next = NULL;
		return;
	}

	//Sets the previous to the inserted
	//Works no matter the postion
	Node *tail = getTail(*list_head);
	tail->next = to_be_inserted;
	to_be_inserted->prev = tail;
	to_be_inserted->next = NULL;
}

/**
 * @param list_head points the start of the list
 * @param to_be_inserted is the node to insert
 * If list_head or to_be_inserted is null it will print a message
 * Based on increasing order of the list the new node will be added
 * If it is smaller than the list_head the pointer to the list_head will be changed
 * If *list_head is NULL then the inserted element will become the entire list
 * Otherwise this method will tranverse the list adding the node where it fits into increasing order
 * @post-conditon list is in order
 */
void ordered_insert(Node **list_head, Node *to_be_inserted)
{
	if (list_head == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value: list head\n");
		return;
	}
	if (to_be_inserted == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value: to_be_inserted\n");
		return;
	}
	//If empty
	if ((*list_head) == NULL)
	{
		*list_head = to_be_inserted;
		to_be_inserted->prev = NULL;
		to_be_inserted->next = NULL;
		return;
	}

	//If it should become the new head of list
	if ((*list_head)->value > to_be_inserted->value)
	{
		to_be_inserted->next = *list_head;
		to_be_inserted->prev = NULL;
		(*list_head)->prev = to_be_inserted;
		*list_head = to_be_inserted;
		return;
	}
	//Inserted in the middle or end of the list
	Node *previ = (*list_head);
	Node *curr = (*list_head)->next;
	int val = to_be_inserted->value;
	int entered = 0;
	while (curr != NULL)
	{
		if (previ->value < val && val < curr->value)
		{
			entered = 1; //Showing it is not the last element
			break;
		}
		previ = curr;
		curr = curr->next;
	}
	//In the middle nodes of the list
	if (entered == 1)
	{
		previ->next = to_be_inserted;
		to_be_inserted->prev = previ;
		to_be_inserted->next = curr;
		curr->prev = to_be_inserted;
	} //In the final node of the list
	else
	{
		previ->next = to_be_inserted;
		to_be_inserted->prev = previ;
	}
}

/**
 * @param list_head is the head of the linked list to be deleted
 * deallocates the memory of each node in the list, starting with the head
 * @post conditon the list is deallocated but can still be printed as head is not set to NULL
 */
void delete_all(Node *list_head)
{
	if (list_head == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value cannot delete a NULL list\n");
		return;
	}
	//Tranverses through the list deallocating each node
	Node *curr = list_head;
	while (curr != NULL)
	{
		Node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

/**
 * @param list_head is the head of the list that contains the node to be deleted
 * @param to_be_deleted contains the node that will be deleted
 * if either of these are null the program will terminate and print out an error message
 * if the node could not be found an error message will be printed out
 * post_condition the noide wll be deleted from the list
 */
void delete (Node **list_head, Node *to_be_deleted)
{
	if ((list_head) == NULL || (*list_head) == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value: list_head\n");
		return;
	}
	if (to_be_deleted == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value: to_be_deleted\n");
		return;
	}
	int val = to_be_deleted->value;
	//If its is a single node list and the list_head needs to be deleted
	if ((*list_head)->next == NULL && (*list_head)->value == val)
	{
		free(*list_head);
		*list_head = NULL;
		return;
	}
	//If the list head is the node to be deleted
	if ((*list_head)->value == val)
	{
		Node *temp = *list_head;
		Node *temp1 = (*list_head)->next;
		free(temp);
		(*list_head) = temp1;
		temp1->prev = NULL;
		return;
	}
	//If the tail of the list needs to be deleted
	if (getTail(*list_head)->value == val)
	{
		Node *tail = getTail(*list_head);
		Node *temp = tail->prev;
		temp->next = NULL;
		free(tail);
		return;
	}
	//2 or more elementsi and not list head
	Node *curr = (*list_head)->next;
	Node *previ = (*list_head); //This is NULL
	while (curr != NULL)
	{
		if (curr->value == val)
		{
			previ->next = curr->next;
			Node *temp = curr->next;
			temp->prev = previ;
			free(curr);
			return;
		}
	}
	fprintf(stderr, "Could not find or delete to_be_deleted\n");
	return;
}

/**
 * @param list_head is the head of the list to be returned
 * This fucntion will return the tail end of the list, if a null head is handed an error message will be printed out
 * It will not modify the list in any way, just an accessor method
 */
Node *getTail(Node *list_head)
{
	if (list_head == NULL)
	{
		fprintf(stderr, "bad input, null pointer not an acceptable input value: list_head\n");
		return NULL;
	}
	Node *curr = list_head;
	Node *prev = list_head->prev; //This will be NULL
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	return prev;
}
