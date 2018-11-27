/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This file contains the code implementation for the data cache.


*/

#include "data_cache.h"

extern struct stats Stats_Cache;
extern struct cache	Data_Cache[SETS][DATA_WAY];

int DataRead(int set_index, int new_tag){
	//Check For Hit or miss, and evict if there is neither
	if(DataHit(set_index, new_tag) == FALSE){
		if(DataMiss(set_index, new_tag) == FALSE)	
			DataEvictLRU(set_index, new_tag);
		return FALSE;
	}
	return TRUE;
}

int DataHit(int set_index, int new_tag){
	for(int i = 0; i < DATA_WAY; i++){
		if((Data_Cache[set_index][i].mesi != I) && (Data_Cache[set_index][i].tag == new_tag))
		{
			DataUpdateLRU(set_index, i);
			Stats_Cache.cache_hit++;
		}
		else if (i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;
}

//This function checks for a miss and takes appropriate action
int DataMiss(int set_index, int new_tag){
	Stats_Cache.cache_miss++;
	for(int i = 0; i < DATA_WAY; i++){
		if(Data_Cache[set_index][i].mesi == I){
			UpdateMESI(set_index, i, n);
			Data_Cache[set_index][i].address = address;
			Data_Cache[set_index][i].tag = new_tag;
			Data_Cache[set_index][i].index = temp_index;
			Data_Cache[set_index][i].b_offset = temp_offset;
			DataUpdateLRU(set_index, i);
			if(mode == 1)
			{
				printf( "Read from L2	<0x%08x>\n", address);		
			}	
					
			return TRUE;
		}
		if(i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;
}

void DataEvictLRU(int set_index, int new_tag){
	for(int i = 0; i < DATA_WAY; i++){
		if(Data_Cache[set_index][i].lru == DATA_WAY - 1){	
		//check which state we are in
			if(Data_Cache[set_index][i].mesi == M){
				if(mode == 1){
					printf("Write to L2 cache    <0x%lx>\n", (long)Data_Cache[set_index][i].address);
					printf("Read for Ownership from L2    <0x%lx>\n", (long)address);
				}
				UpdateMESI(set_index, i, n);
				Data_Cache[set_index][i].address = address;
				Data_Cache[set_index][i].tag = new_tag;	
				Data_Cache[set_index][i].index = temp_index;
				Data_Cache[set_index][i].b_offset = temp_offset;
				DataUpdateLRU(set_index, i);
			}
			else{
				if(mode == 1){
					printf("Write to L2 cache    <0x%lx>\n", (long)Data_Cache[set_index][i].address);
					printf("Read from L2    <0x%lx>\n", (long)address);
				}
				UpdateMESI(set_index, i, n);
				Data_Cache[set_index][i].address = address;
				Data_Cache[set_index][i].tag = new_tag;	
				Data_Cache[set_index][i].index = temp_index;
				Data_Cache[set_index][i].b_offset = temp_offset;
				DataUpdateLRU(set_index, i);
			}
			return;
		}
	}
	return;
}

/*
	Functions in the Data Cache that aren't part of normal operations

*/

void DataClear(void){
	for(int index1 = 0; index1 < SETS; index1++)
	{
		for(int index2 = 0; index2 < DATA_WAY; index2++)
		{
			//This line needs to be revised
			Data_Cache[index1][index2].lru = -1; //decrement LRU values
			Data_Cache[index1][index2].mesi = I;	//v	
		}
	}
	return;
}


void PrintDataCache(){
	for(int index_set = 0; index_set < SETS; index_set++){
		for(int index_line = 0; index_line < DATA_WAY; index_line++){
			if(Data_Cache[index_set][index_line].mesi != I){
				printf("-----\n");
				printf("MESI: %d LRU: %d Address: %lx \n", 
					Data_Cache[index_set][index_line].mesi,
					Data_Cache[index_set][index_line].lru,
					(long)Data_Cache[index_set][index_line].address);
			}
		}
	}
	return;
}
