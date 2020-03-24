/**
 * Jake Armendariz
 * 1650932
 * 12M, January 25, 2019
 * 
 * struct_test.c demos using structures with and without pointers
 * the rider struct has basic data types for structures
 * The program simmply designs to riders and prints out its contents two different ways
 * Since there is no UI there are no limits, the program simply prints what was provided
 *
 */
#include<stdio.h>
#include<stdlib.h>

#define MAX_INITIALS 2 // two character initials
struct rider {
	 int ID; // rider’s unique identifier
	 char riderInitials[MAX_INITIALS+1]; // +1 for NULL character to terminate string
	 int ave_rating; // rating out of possible 100 points
	 int age; //Age of the uber rider
	 int distance;//Distance traveled
	 struct rider *next;

} typedef rider_st;


void standard(rider_st *rptr){
	 rptr->ID = 10;
         rptr->riderInitials[0] = 'A';
         rptr->riderInitials[1] = 'B';
         rptr->riderInitials[2] = '\0';
         rptr->ave_rating = 100;
         rptr->age = 25;
         rptr->distance = 1000;
        //rptr->next = null;
}

void printRiderList( rider_st *r){
while (r != NULL) {
        printf("rider at address %p\n rider ID = %d\n rider initials = %s\n rider average rating = %d/100\n rider age = %d\n rider distance = %d\n", r, r->ID, r->riderInitials, r->ave_rating, r->age, r->distance);
	r = r->next;

 }
}

// Print the contents of the rider structure given by the reference pointer r.
// // If the reference is null, quietly return and generate no errors.
void printRider( rider_st *r){
if (r != NULL) {
	printf("rider at address %p\n rider ID = %d\n rider initials = %s\n rider average rating = %d/100\n rider age = %d\n rider distance = %d\n", r, r->ID, r->riderInitials, r->ave_rating, r->age, r->distance);    
 }
}


//     //
//     // Little testing program to allocate a structure and fill in the contents of structure
//     // as well as use statically allocated structure.
//     //
int main()
{
 	rider_st *rptr;
 	rider_st *one;
	rider_st *two;
	rider_st *three;
	
 	/* allocate space for a rider node */
 	rptr = malloc( sizeof(rider_st));
	one = malloc( sizeof(rider_st));
	two = malloc( sizeof(rider_st));
	three = malloc( sizeof(rider_st));
	printf("Size of rider is %d\n", (int)sizeof(rider_st));
 	/* initialize contents */
 	rptr->ID = 10;
	 rptr->riderInitials[0] = 'J';
	 rptr->riderInitials[1] = 'A';
	 rptr->riderInitials[2] = '\0';
	 rptr->ave_rating = 100;
	 rptr->age = 25;
	 rptr->distance = 1000;



	 rptr->next = one;
	 one->next = two;
	 two->next = three;
	three->next = NULL; 	
	 //printRider(rptr);
	 /* initialize statically allocated rider structure contents *
	 rider.ID = 101;
	 rider.riderInitials[0] = 'X';
	 rider.riderInitials[1] = 'Z';
	 rider.riderInitials[2] = '\0';
	 rider.ave_rating = 50;
	 rider.age = 30;
	 rider.distance = 2300;
	 printRider(&rider);
	*/

	standard(one);
	standard(two);
	standard(three);
//	four = null;
	printRiderList(rptr);
	
	//printRider(one);
	//printRider(two);
	//printRider(three);
//	printRider(four);



	 free(rptr);
	free(one);
	free(two);
	free(three);

	 return EXIT_SUCCESS;
}
