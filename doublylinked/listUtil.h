/**
 * Jake Armendariz
 * 1650932
 * 12B Assignment 2
 * Febuary 7, 2019
 *
 * Description
 * Contains the functions used by main to test list.c
 * Its pretty simple
 */
#include "list.h"

/**
 *  * Prints an individual node
 *   * Will print its contents and its previous and following node as well
 *    * If it is at the front or back of list it will tell that it is NULL
 */
void printNode(NodeObj *a);

/**
 *  * Prints the full linked list
 *   * Uses the printNode method so it will tell the contents of the current nodes value and the previous and post nodes as well
 */
void printNodeList(NodeObj *list_head);
