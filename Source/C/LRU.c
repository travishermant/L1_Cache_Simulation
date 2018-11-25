/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	LRU = 0, MRU = 7
*/

#include "LRU.h"
extern struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];

int InstUpdateLRU(int set, int way, int lru)  //Use struct cache variables
{
	int check = 0;
	
	if(Inst_Cache[set][way] != NULL){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Inst_Cache[set][way].lru = 7;
		while(way != 8){
			++way;
			Inst_Cache[set][way].lru = (lru - 1);
		}
	check = 0;
	}
	else if(Inst_Cache[set][way] == NULL){
	// Initializing the cache, so NULL means empty way
		Inst_Cache[set][way].lru = way - 1;
		check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
return check;
}

int DataUpdateLRU(int set, int way, int lru)  //Use struct cache variables
{
	int check = 0;
	
	if(Data_Cache[set][way] != NULL){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Data_Cache[set][way].lru = 7;
		while(way != 8){
			++way;
			Data_Cache[set][way].lru = (lru - 1);
		}
	check = 0;
	}
	else if(Data_Cache[set][way] == NULL){
	// Initializing the cache, so NULL means empty way
		Data_Cache[set][way].lru = way - 1;
		check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
return check;
}
