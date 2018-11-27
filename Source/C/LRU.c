/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	LRU = 0, MRU = 7 for DATA CACHE
	LRU = 0, MRU = 3 for INSTRUCTION CACHE
*/

#include "LRU.h"

int InstUpdateLRU(int set, int way)  //Use struct cache variables
{
	int check = 0;
	
	if(Inst_Cache[set][way].lru >= 0 ){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Inst_Cache[set][way].lru = 3;
		while(way != 4){
			++way;
			Inst_Cache[set][way].lru = (Inst_Cache[set][way].lru - 1);
		}
	check = 0;
	}
	else if(Inst_Cache[set][way].lru == -1){
	// Initializing the cache, so -1 means empty way
		Inst_Cache[set][way].lru = INST_WAY - 1;
		check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
return check;
}

int DataUpdateLRU(int set, int way)  //Use struct cache variables
{
	int check = 0;
	
	if(Data_Cache[set][way].lru >= 0){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Data_Cache[set][way].lru = 7;
		while(way != 8){
			++way;
			Data_Cache[set][way].lru = (Data_Cache[set][way].lru - 1);
		}
	check = 0;
	}
	else if(Data_Cache[set][way].lru == -1){
	// Initializing the cache, so NULL means empty way
		Data_Cache[set][way].lru = DATA_WAY - 1;
		check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
return check;
}
