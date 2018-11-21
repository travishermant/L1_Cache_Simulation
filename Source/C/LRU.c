/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	LRU = 0, MRU = 7
*/

#include "LRU.h"
extern struct cache thecache;

int lru_update(int set ,int way, int tag, int hit, int miss, int lru)  //Use struct cache variables
{
	int check = 0;
	
	if((hit || miss) && thecache[set][way] != NULL){
	// Set way with current tag to MRU
	// Decrement LRU bits to the right of the MRU
		thecache[set][way].lru = 7;
		while(way != 8){
			++way;
			thecache[set][way].lru = (lru - 1);
		}
	check = 0;
	}
	else if(thecache[set][way] == NULL){
	// Initializing the cache, so NULL means empty way
		thecache[set][way].lru = way - 1;
	check = 0;
	}
	else
		check = 1;
	
// Returns 0 if went through successfully
// Else returns 1
	
reutrn check;
}
