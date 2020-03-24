/**
 * Jake Armendariz
 * 1650932
 * 12B
 * January 30, 2019
 * This is a header file containing a rider struct that will be used in list.c
 * It contains a couple elements for idenifing and measuring
 */
struct rider {
	 int ID; /* ID of the rider, internal code */
	 char *first_name; /* name of rider, first */
	 char *last_name; /* name of rider, second */
		 int ave_rating; /* average rating over all rides taken */
	 double distance; /* miles from driver */
	 struct rider *next;
} typedef rider_st;

rider_st *create_new_rider(int id, char *first_name, char *last_name, double ave_rating, double distance);
void front_insert(rider_st **ptr_to_list_head, rider_st *to_be_inserted);
void end_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted);
void ordered_insert (rider_st **ptr_to_list_head, rider_st *to_be_inserted);
void delete_all (rider_st *list_head);
void delete(rider_st **ptr_to_list_head, rider_st *to_be_deleted);
rider_st *find(rider_st *list_head, int ID);
rider_st *standard();//Fills a standard rider to save time will testing
void printRiders(rider_st *rider);//Prints Rider
void sort_list(rider_st **ptr_to_list_head);//Sorts the list to ensure the ordered insert works correctly
void transfer_data(rider_st *og, rider_st *cpy);//Transfers data from one node to another

