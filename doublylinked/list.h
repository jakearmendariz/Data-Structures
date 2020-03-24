/**
 * Jake Armendariz
 * 1650932
 * Assignment2
 * 12B
 * Febuary 7, 2019
 *
 * Description:
 * This is a header file for list.c declares Node for listUtil.c as well
 */

/**
 * This is the basic node that is used to demonstate doubly linked lists
 */
typedef struct Node
{
	int value;
	struct Node *prev;
	struct Node *next;
} Node;
/**
 * @param id is the id of the new node
 * Allocates memory for the new node and returns null if memory allocation fails
 * @returns a new Node
 */
Node *create_new_node(int id);

/**
 *  * @param list head is the head or top of a list
 *   * @param to_be_inserted is the ptr that will go at the tail end of the list
 *    * Takes the to_be_inserted and sends it the end of the list. Changes the nearby pointers to make it easier
 *     * Using my getTail method to find the end of list
 *      * If a null ptr is given the function will print out an error message and terminate
 *       * post_condition, the list will be inserted
 */
void insert(Node **list_head, Node *to_be_inserted);

/**
 *  * @param list_head points the start of the list
 *   * @param to_be_inserted is the node to insert
 *    * If list_head or to_be_inserted is null it will print a message
 *     * Based on increasing order of the list the new node will be added
 *      * If it is smaller than the list_head the pointer to the list_head will be changed
 *       * If *list_head is NULL then the inserted element will become the entire list
 *        * Otherwise this method will tranverse the list adding the node where it fits into increasing order
 *         * @post-conditon list is in order
 */
void ordered_insert(Node **list_head, Node *to_be_inserted);

/**
 *  * @param list_head is the head of the linked list to be deleted
 *   * deallocates the memory of each node in the list, starting with the head
 *    * @post conditon the list is deallocated but can still be printed as head is not set to NULL
 */
void delete_all(Node *list_head);

/**
 * @param list_head is the head of the list that contains the node to be deleted
 *  * @param to_be_deleted contains the node that will be deleted
 *   * if either of these are null the program will terminate and print out an error message
 *    * if the node could not be found an error message will be printed out
 *     * post_condition the noide wll be deleted from the list
 */
void delete (Node **list_head, Node *to_be_deleted);
//void delete_value(Node **list_head, Node *to_be_deleted);

/**
 *  * @param list_head is the head of the list to be returned
 *   * This fucntion will return the tail end of the list, if a null head is handed an error message will be printed out
 *    * It will not modify the list in any way, just an accessor method
 */
Node *getTail(Node *list_head);
