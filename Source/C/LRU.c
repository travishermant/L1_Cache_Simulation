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
	
	if(Inst_Cache[SETS][INST_WAY].lru >= 0 ){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Inst_Cache[SETS][INST_WAY].lru = 3;
		while(way != 4){
			++way;
			Inst_Cache[SETS][INST_WAY].lru = (Inst_Cache[SETS][INST_WAY].lru - 1);
		}
	check = 0;
	}
	else if(Inst_Cache[SETS][INST_WAY].lru == -1){
	// Initializing the cache, so -1 means empty way
		Inst_Cache[SETS][INST_WAY].lru = way - 1;
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
	
	if(Data_Cache[SETS][DATA_WAY].lru >= 0){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		Data_Cache[SETS][DATA_WAY].lru = 7;
		while(way != 8){
			++way;
			Data_Cache[SETS][DATA_WAY].lru = (Data_Cache[SETS][DATA_WAY].lru - 1);
		}
	check = 0;
	}
	else if(Data_Cache[SETS][DATA_WAY].lru == -1){
	// Initializing the cache, so NULL means empty way
		Data_Cache[SETS][DATA_WAY].lru = way - 1;
		check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
return check;
}
