/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This file contains the code implementation for the data cache.


*/

#include "data_cache.h"

//	This function handles the flow for the data cache
// 	If the data isn't hit, it will then go to see if there is an empty way to fill
//	If there's no empty way, it will then evict the LRU
int DataRead(int set_index, int new_tag){
	if(DataHit(set_index, new_tag) == FALSE){
		if(DataMiss(set_index, new_tag) == FALSE)	
			DataEvictLRU(set_index, new_tag);
		return FALSE;
	}
	return TRUE;
}

//  Checking if the tag is present in the set, and updating the MESI and LRU if it's needed
int DataHit(int set_index, int new_tag){
	for(int i = 0; i < DATA_WAY; i++){
		if((Data_Cache[set_index][i].mesi != I) && (Data_Cache[set_index][i].tag == new_tag)){
			miss = FALSE;
			UpdateMESI(set_index, i, n);
			DataUpdateLRU(set_index, i);
			Stats_Cache.cache_hit++;
			return TRUE;
		}
		else if (i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;
}

//  If DataHit doesnt find it, then this function will check for an empty way and fill the data in there
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
				printf( "Read from L2	<0x%08x>\n", address);		
			return TRUE;
		}
		if(i == DATA_WAY - 1)
			return FALSE;
	}
	return TRUE;
}

//  If there are no empty ways found in DataMiss, then evict the way that is LRU
//  If data is modified, then write to L2 cache and read for ownership, otherwise just read from L2
void DataEvictLRU(int set_index, int new_tag){
	miss = TRUE;
	for(int i = 0; i < DATA_WAY; i++){
		if(Data_Cache[set_index][i].lru == 0){	
		//check which state we are in
			if(mode == 1){
				if((Data_Cache[set_index][i].mesi == M) && (n != 1){
					printf("Write to L2 cache    <0x%lx>\n", (long)Data_Cache[set_index][i].address);
				else if((Data_Cache[set_index][i].mesi == M) && (n == 1)
					printf("Read for Ownership from L2    <0x%lx>\n", (long)address);
				}
				else{
					printf("Read from L2    <0x%lx>\n", (long)address);
				}
			}
			UpdateMESI(set_index, i, n);
			Data_Cache[set_index][i].address = address;
			Data_Cache[set_index][i].tag = new_tag;	
			Data_Cache[set_index][i].index = temp_index;
			Data_Cache[set_index][i].b_offset = temp_offset;
			DataUpdateLRU(set_index, i);
			return;
		}
	}
	return;
}

/*
	Functions in the Data Cache that aren't part of normal operations

*/

// Clears the entire data cache, changes MESI to I, and LRU to -1
void DataClear(void){
	for(int index1 = 0; index1 < SETS; index1++){
		for(int index2 = 0; index2 < DATA_WAY; index2++){
			Data_Cache[index1][index2].lru = -1; //decrement LRU values
			Data_Cache[index1][index2].mesi = I;	//v	
		}
	}
	return;
}

// Prints all the contents of the data cache, provided that they are not Invalid
void PrintDataCache(){
	printf("\n~~~~~~~~~~~~~ DATA_CACHE ~~~~~~~~~~~~~\n");
	for(int index_set = 0; index_set < SETS; index_set++){
		for(int index_line = 0; index_line < DATA_WAY; index_line++){
			if(Data_Cache[index_set][index_line].mesi != I){
				printf("-----\n");
				printf("SET: %lx WAY: %d MESI: %d LRU: %d ADDRESS: %lx \n", 
					(long)Data_Cache[index_set][index_line].index,
					index_line + 1,
					Data_Cache[index_set][index_line].mesi,
					Data_Cache[index_set][index_line].lru,
					(long)Data_Cache[index_set][index_line].address);
					
			}
		}
	}
	return;
}
