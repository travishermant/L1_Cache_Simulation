/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This is the header file for the data cache.
	It contains the needed libraries and function declarations for 
	the data cache.

*/

#include "main.h"
#include "LRU.h"
#include "MESI.h"

// declarations for variables
//File Access


//Function declarations
int read_data(int set_index, int tag_size);	//function for reading the data
int data_hit_check(int set_index, int tag_size);	//function that checks for data hit
int data_miss_check(int set_index, int tag_size);	//function that checks for data miss
void data_clear_cache(void);	//function that clears the data cache
void data_line_evict_LRU(int set_index, int i);	// function that evicts the LRU



