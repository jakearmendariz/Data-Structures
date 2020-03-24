/**
 * Jake Armendariz
 * 1650932
 * 12B
 * January 31, 2019
 *
 * list.c uses list.h to manipulate a linked list of rider_st structs
 * Through a number of functions this file has the ability to add, delete, find and remove nodes
 * It has the option of sorting the list via bubble sort in the sort_list method
 * This program can manipulate linked lists of size 0->very very big.
 */
#include  "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * create_new_rider returns a pointer to a rider_st struct that has contains the values of the parameters
 * Allocates space for the pointer
 * Does not allocate for strings first_name and last_name
 * @return the filled rider_st struct
 */
rider_st *create_new_rider(int id, char *first_name, char *last_name, double ave_rating, double distance){
//	printf("\nCreating new rider\n");
	rider_st *r = (rider_st*)malloc(sizeof(rider_st));
	char* first = (char*)malloc(sizeof(char)*100);
	char* last  = (char*)malloc(sizeof(char)*100);
	strcpy(first, first_name);
	strcpy(last, last_name);
	r->ID = id;
	r->first_name = first;
	r->last_name = last;
	r->ave_rating = ave_rating;
	r->distance = distance;
	r->next = NULL;
	return r;
}
/**
 * @param rider should be the head of a list
 * This program will run through the list starting at rider printing out the details of whole list
 * If there is a circular linked list, an error. It will terminate printing after 1000. This is mainly for testing new code with pointers
 */
void printRiders(rider_st *rider){
	int counter = 0;
	while(rider != NULL){
		printf("Rider Node: ID=%d, first_name=%s, last_name=%s, average_rating %d/100, distance %f, next=%p \n",rider->ID, rider->first_name, rider->last_name, rider-> ave_rating, rider->distance, rider->next);
		rider = rider->next;
		counter++;
		if(counter > 1000)
			break;
	}
	printf("\n");
}




/**
 * @param ptr_to_list_head points to the current list head
 * @param to_be_inserted is the pointer that will be inserted into the list
 * pre-condition: Both functions are initialized and memory has already been allocated
 * post-conditon:The head now refers to the node that was inserted and the linked list is one size larger
 */
void front_insert(rider_st **ptr_to_list_head, rider_st *to_be_inserted){
	if(to_be_inserted == NULL){
		printf("Can't insert a null pointer\n");
		return;
	}	
	//By making the new elements pointer to reference the head it becomes the head
	to_be_inserted->next = *ptr_to_list_head;
	*ptr_to_list_head = to_be_inserted;
}


/**
 * @param ptr_to_list_head points to the current list head
 * @paran to_be_inserted is the pointer that will be inserted into the list
 * Inserts the second parameter to the end of the lit
 * post-condition: The list begins with the first param and ends with second param
 */
void end_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted){
	//If the list head is null then there is no list to join
	if(to_be_inserted == NULL){
		printf("Error: null pointer in end_insert\n");
		return;
	}
	//If the list head is empty
	if(*ptr_to_list_head == NULL){
		front_insert(ptr_to_list_head, to_be_inserted);
		return;
	}
	//current will hold the place of each struct as it passes trhough the list to find the end
	rider_st *current = *ptr_to_list_head;
	while(current->next != NULL){
		current = current->next;
	}
	//At this point the end of the linked list is current, so now we set its next pointer to the struct to be inserted :)
	current->next = to_be_inserted;
//	printf("current's name is %s %s\n", current->first_name, current->last_name);

}

/**
 * In order to insert something in order of distance the linked list must be ordered
 * I called the sort list method. Once this is done we must check the list and add whereever the distance fits
 * @param ptr_to_list_head is the top of the list and will point to the top even if the new element fills that position
 * @param to_be_inserted will be inserted whereever based off of distance
 * post-condition and ordered linked list from least to greatest by distance
 */
void ordered_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted){
	//List needs to be sorted before it can be added in a specific order
	if(to_be_inserted == NULL){
		printf("Can't insert a null pointer in ordered_insert\n");
		return;
	}
	sort_list(ptr_to_list_head);
//	printRiders(*ptr_to_list_head);
	double dist = to_be_inserted->distance;
	rider_st *current = *ptr_to_list_head;
	//Size zero linked list
	if(current == NULL){
		front_insert(ptr_to_list_head, to_be_inserted);
		return;
	}
	//Size one linked list
	if(current->next == NULL){
		if(current->distance < dist){
			current->next = to_be_inserted;
		}
		else{
			to_be_inserted->next = current;
			*ptr_to_list_head = to_be_inserted;
		}
		return;
	}
	//Size >= 2
	int counter = 0;
	rider_st *prev = (rider_st*)malloc(sizeof(rider_st));
	while(current != NULL){
		//List head is bigger
		if(current->distance > dist && counter ==0){
			front_insert(ptr_to_list_head, to_be_inserted);
			break;
		}
		//After the list head
		else if(current->distance > dist){
//			printf("\nIn the right place\n");
			prev->next = to_be_inserted;
			to_be_inserted->next = current;
			break;
		}
		counter++;
		prev = current;
		current = current->next;
	}
	//free(prev);
	
}


/**
 * Transfers data between two nodes
 * @param og is the original
 * @param cpy is the copy
 * All of the data from og will be put in cpy except for the next ptr
 */
void transfer_data(rider_st *og, rider_st *cpy){
			char *first = malloc(255*sizeof(char));
                        char *last = malloc(255*sizeof(char));
                        strcpy(first, og->first_name);
                        strcpy(last, og->last_name);
                   
                   //    strcpy(cpy->first_name, og->last_name);
		//	strcpy(cpy->last_name, og->last_name);
			 cpy->ID = og->ID;
                        cpy->ave_rating = og->ave_rating;
                        cpy->distance = og->distance;
                  //      cpy->next = og->next;
			cpy->first_name = first;
			cpy->last_name = last;
	//		free(first);
	//		free(last);

}


/**
 * This orders the list by distance from least to greatest
 * I am not sure if this method was suppose to be created for the ordered insert
 * It uses a bubble sort algorithm
 * The commented out code was my attempted to make an ordered list via list pointers
 * I ended up just switching out the data. I left the code commented out because I wanted to be able to work on
 * it in the future when I know more stuff or have free time.
 */
void sort_list(rider_st **ptr_to_list_head){
	int counter = 0;
	//Counts the list, keeps the pointer in tact
	rider_st *current = *ptr_to_list_head;
	 while(current != NULL){
 		counter++;
                current = current->next;
        }
	//If size 1 or 0
	if(counter <= 1){
		return;
	}
	current = *ptr_to_list_head;
//	rider_st *prev = malloc(sizeof(rider_st));
//	prev = NULL;
	rider_st *temp = malloc(sizeof(rider_st));
	//Go through the list moving the elemeents when their ID is getting smaller
	//Using two for loops I traverse the linked list, if ID of following position is bigger it swaps the data between the nodes 
	
	 for(int j = 0; j < counter-1; j++){
		current = *ptr_to_list_head;
	//	prev = NULL;
		for(int i = 0; i < counter-1; i++){	
			//I attempted to rearrage the nodes using their pointers but for the sake of time I chose to submit the data chaning version
			if(current->distance >  current->next->distance){
/*				if(prev == NULL){//If this is the head node
					printf("\nRearranging top elements\n");
		//			rider_st *b = current->next;
		//			rider_st *c = b->next;
					current->next  = current->next->next;
					current->next->next = current;
					*ptr_to_list_head = current->next;
				}
				else if(i < counter-2){
/					printf("\nRearranging middle nodes\n");
				//	rider_st *node1 = current;
					printf("Before node2 intialization");
					rider_st *node2 = current->next;
					printf("before");
					rider_st *node3 = current->next->next;
					printf("after");
					prev->next = node2;
					node2->next = current;
					current->next = node3;
					//prev = node2;
/					
				}
				else if(i == counter -2){
					printf("\nRearragning bottom nodes\n");
	//				rider_st *b = current;
	//				rider_st *c = current->next;
	//				current->next = NULL;
					prev->next = current->next;
					rider_st **c  = &(current->next);
					(*c)->next = current;
					current->next = NULL;
					 
				}
				
*/				
				
	//			rider_st *temp = malloc(sizeof(rider_st));
				//In order to sort the riders I just moved the data inside of them around becuas
				// I couldn't figure out the next pointer and I needed more
				//study time for this midterm. I'm also pretty sure this method isn't mandatory
				transfer_data(current, temp);
				rider_st *node1 = current;
                	        rider_st *node2 = current->next;
				//Moves the data, keeping the head of the list at the head
				transfer_data(node2, node1);
				transfer_data(temp, node2);			
			}
	//	prev = current;
		current = current->next;
			
		}
	}
	//free(temp);
	//free(current);
}



/**
 * @param list_head is the head of the list to be deleted
 * pre-conditon all nodes have been allocated
 * post-condition all nodes have been deallocated including their strings :)
 * The value of list head will change as it traverses through list
 */
void delete_all (rider_st *list_head){
	rider_st *current = list_head;
	rider_st *temp;
	while(current != NULL){
		printf("\nBegin names..");
		free(current->first_name);
		free(current->last_name);
		temp = current->next;
		printf("Begin freeing struct..");
		free(current);
		printf("Finnish freeing round\n");
		current = temp;
	}
}





/**
 * @param ptr_to_list_head is the list head
 * @param to_be_deleted is the node to be deleleted
 * This function locates a given node based off of it's ID, then if found it will deallocate it
 * The prev spot will hold the deleted nodes pointer so it keeps a solid structure
 * if the node is not found a message is printed out
 */
void delete(rider_st **ptr_to_list_head, rider_st *to_be_deleted){
	int complete = 0;
	if(*ptr_to_list_head == NULL || to_be_deleted == NULL){
		printf("\nNull pointers error in fucntion delete\n");
		return;
	}
	//If the head is the string to be deleted
	if((*ptr_to_list_head)->ID == (to_be_deleted->ID)){
		free((*ptr_to_list_head)->first_name);
		free((*ptr_to_list_head)->last_name);
		free(to_be_deleted);
		complete = 1;
	}
	else{//If its any other string it won't be deleted
		rider_st *current = *ptr_to_list_head;
		while(current->next != NULL){
			if(current->next->ID == to_be_deleted->ID){
				free(to_be_deleted->first_name);
				free(to_be_deleted->last_name);
				current->next = to_be_deleted->next;
				free(to_be_deleted);
				complete=1;
				break;
			}
		}
		
		
	}
	//If the node was not deleted it will print out tthis message
	if(complete == 0){
		printf("\nRider ID:%d was not deleted, couldn't find in list\n", to_be_deleted->ID);
	}
}

/**
 * @param list_head is the first node in the list to search
 * @param ID is the ID of the node being searched for
 * Locates the rider with the given ID
 * If no rider is found then NULL is returned
 */
rider_st *find(rider_st *list_head, int ID){
	while(list_head != NULL){
		if(list_head->ID == ID){
			return list_head;}
		list_head = list_head->next;
	}
	//Only reaches this point if it was not found
	return NULL;
	
}

