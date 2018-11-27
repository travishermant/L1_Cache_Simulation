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
extern uint32_t address, temp_tag, temp_index, temp_offset;
extern int	mode, n;	
extern struct stats Stats_Cache;
extern struct cache	Data_Cache[SETS][DATA_WAY];

//Function declarations
int DataRead(int set_index, int tag_size);	//function for reading the data
int DataHit(int set_index, int tag_size);	//function that checks for data hit
int DataMiss(int set_index, int tag_size);	//function that checks for data miss
void DataClear(void);	//function that clears the data cache
void DataEvictLRU(int set_index, int i);	// function that evicts the LRU
void PrintDataCache();


