/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This is the header file for the data cache.
	It contains the needed libraries and function declarations for 
	the data cache.

*/

#include <main.h>
#include <stdio.h>
#include <stdint.h>	
#include <LRU.h>

// declarations for variables
//File Access
extern FILE *output_text;

extern int index_bits;
extern int byte_select;
extern int tag_size;
extern int i;
extern struct cache_line cache_data[DATA_SETS][DATA_WAY];
extern int data_hit;
extern int data_miss;
extern uint32_t address;
extern int byte_select;
extern int mode_select;
extern int check_evict;
extern int event;

//Function declarations
unsigned long address_grab(int set_index, int i);	//function that gets the address
int read_data(int set_index, int tag_size);	//function for reading the data
void MESI_function(int event, int set_index, int address);	//function for the MESI protocol
void data_statistics();	//function for logging the data
int data_hit_check(int set_index, int tag_size);	//function that checks for data hit
int data_miss_check(int set_index, int tag_size);	//function that checks for data miss
void data_clear_cache(void);	//function that clears the data cache
int data_LRU_update(int set_index, int i);	//function that updates the LRU
void data_line_evict_LRU(int set_index, int i);	// function that evicts the LRU



