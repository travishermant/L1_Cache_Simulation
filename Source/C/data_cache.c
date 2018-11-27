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
	//Check For Hit or miss, and evict if there is neither
	if(DataHit(set_index, tag_size) == FALSE){
		if(DataMiss(set_index, tag_size) == FALSE)	
			DataEvictLRU(tag_size, set_index);
		return FALSE;
	}
		// printf("Error. DataRead cannot call evict because there was a hit or a miss");
		return TRUE;
}
// This function checks for a hit and takes appropriate action
int DataHit(int set_index, int tag_size)
{
	for(int i = 0; i < DATA_WAY; i++)
	{
	// Check if the tag bits are equivalent and check if the state is valid
		if(Data_Cache[set_index][i].mesi != I && Data_Cache[set_index][i].tag == tag_size)
		{
			DataUpdateLRU(set_index, i);
		}
		else if (i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;


}

//This function checks for a miss and takes appropriate action
int DataMiss(int set_index, int tag_size)
{

	for(int i = 0; i < DATA_WAY; i++)
	{
		if(Data_Cache[set_index][i].mesi == I)
		{
			// MESI update?
			UpdateMESI(set_index, i, n);
			Data_Cache[set_index][i].address = address;
			Data_Cache[set_index][i].tag = tag_size;
			Data_Cache[set_index][i].index = temp_index;
			Data_Cache[set_index][i].b_offset = temp_offset;
			DataUpdateLRU(set_index, i);	//lruupdate function still unsure how it works
			return TRUE;
		}
		if(i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;
}

// This function checks the index and way, and clears the
// content of the cache by resetting LRU to NULL, and setting the MESI bits to invalid (3). 

void DataClear(void)
{
	int index1 = 0;	//set index
	int index2 = 0; //way index

	for(index1 = 0; index1 < SETS; index1++)
	{
		for(index2 = 0; index2 < DATA_WAY; index2++)
		{
			//This line needs to be revised
			Data_Cache[index1][index2].lru = -1; //decrement LRU values
			Data_Cache[index1][index2].mesi = I;	//v	
		}
	}

}

// The purpose of this function is to evict the LRU.
void DataEvictLRU(int tag_size, int set_index)
{

	int index2 = 1;
	for(index2; index2 < DATA_WAY; index2++)
	{
		if(Data_Cache[set_index][index2].lru == DATA_WAY - 1)
		{	
		//check which state we are in
			if(Data_Cache[set_index][index2].mesi == M)
			{
				Data_Cache[set_index][index2].tag = tag_size;	
				DataUpdateLRU(tag_size, set_index);		//probably wrong
				//printf("Write to L2 cache	<0x%08x>\n", address);
			}
			else
			{
				Data_Cache[set_index][index2].tag = tag_size;
				DataUpdateLRU(tag_size, set_index);
			}
		}
		return;
	}

}

void PrintDataCache(){
	for(int index_set = 0; index_set < SETS; index_set++){
		for(int index_line = 0; index_line < DATA_WAY; index_line++){
			if(Data_Cache[index_set][index_line].mesi != I){
				printf("-----\n");
				printf("MESI: %d LRU: %d Address: %lx \n", 
					Data_Cache[index_set][index_line].mesi,
					Data_Cache[index_set][index_line].lru,
					Data_Cache[index_set][index_line].address);
			}
		}
	}
}
