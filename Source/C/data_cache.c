/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This file contains the code implementation for the data cache.


*/

#include "data_cache.h"

extern struct stats Stats_Cache;
extern struct cache	Data_Cache[SETS][DATA_WAY];


//This function performs three checks,
// Checks if there is a miss, if there is then the miss will be delt
// with accordingly.
// If there is a hit, then data evict will be called.
int DataRead(int set_index, int tag_size)
{
	//Check For Hit or miss, and eveict if there is neither
	if(DataHit(set_index, tag_size) == 0 && DataMiss(tag_size, set_index) == 0)
	{	
		DataEvictLRU(tag_size, set_index);
		return 0;
	}
		printf("Error. DataRead cannot call evict because there was a hit or a miss");
		return 1;
}
// This function checks for a hit and takes appropriate action
int DataHit(int set_index, int tag_size)
{
	for(i = 0; i < DATA_WAY; i++)
	{
	// Check if the tag bits are equivalent and check if the state is valid
		if(cache_data[set_index][i].mesi != 3 && cache_data[set_index][i].TAG == tag_size)
		{
			DataUpdateLRU(set_index, i, cache_data[set_index][i].TAG, cache_data[set_index][i].LRU);
		}
		else if (i == DATA_WAY - 1)
			return 0;
	}
	return 2;


}

//This function checks for a miss and takes appropriate action
int DataMiss(int set_index, int tag_size)
{

	for(i = 0; i < DATA_WAY; i++)
	{
		if(cache_data[set_index][i].mesi == 3)
		{
			//cache_data[set_index][i].ADDRESS = address;
			cache_data[set_index][i].TAG = tag_size;
			DataUpdateLRU(set_index, i, tag_size, cache_data[set_index][i].LRU);	//lruupdate function still unsure how it works
			return 1;
		}
		if( i == DATA_WAY - 1)
		return 0;
	}
	return 2;
}

// This function checks the index and way, and clears the
// content of the cache by resetting LRU to NULL, and setting the MESI bits to invalid (3). 

void DataClear(void)
{
	int index1 = 0;	//set index
	int index2 = 0; //way index

	for(index1 = 0; index1 < DATA_SETS; index1++)
	{
		for(index2 = 0; index2 < DATA_WAY; index2++)
		{
			//This line needs to be revised
			cache_data[index1][index2].lru = NULL; //decrement LRU values
			cache_data[index1][index2].mesi = 3;	//v	
		}
	}

}

// The purpose of this function is to evict the LRU.
void DataEvictLRU(int tag_size, int set_index)
{

	int index2 = 1;
	for(index2; index2 < DATA_WAY; index2++)
	{
		if(cache_data[set_index][index2].lru == DATA_WAY)
		{	
		//check which state we are in
			if(cache_data[set_index][index2].mesi == 0)
			{
				cache_data[set_index][index2].tag = tag_size;	
				DataUpdateLRU(tag_size, set_index);
				printf("Write to L2 cache");
			}
			else
			{
				cache_data[set_index][index2].tag = tag_size;
				DataUpdateLRU(tag_size, set_index);
			}
		}
		return;
	}

}

