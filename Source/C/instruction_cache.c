/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

-Instruction cache acts as a buffer memory between external memory 
and the processor.
-When code executes, instruction sets are copied into the Instruction 
Cache for direct access by the core processor
-instruction cache doesnt write 
- Way 4
- LRU is 2 bit, 0-3

//MESI
#define	M				0
#define	E				1
#define	S				2
#define	I				3

*/

#include "instruction_cache.h"

//	This function handles the flow for the instruction cache
// 	If the instruction isn't hit, it will then go to see if there is an empty way to fill
//	If there's no empty way, it will then evict the LRU
int InstRead(int set_index, int new_tag){	
	if(InstHit(set_index, new_tag) == FALSE){
		if(InstMiss(set_index, new_tag) == FALSE)	
			InstEvictLRU(set_index, new_tag);
		return FALSE;
	}
	return TRUE;
}

//  Checking if the tag is present in the set, and updating the MESI and LRU if it's needed
int InstHit(int set_index, int new_tag){
	for(int idc = 0; idc < INST_WAY; idc++){
		if((Inst_Cache[set_index][idc].tag == new_tag) && (Inst_Cache[set_index][idc].mesi != I)){
				UpdateMESI(set_index, idc, n);
				InstUpdateLRU(set_index, idc);
				Stats_Cache.cache_hit++; //increment hit counter
				return TRUE;
			}
		else if (idc == INST_WAY - 1)
				return FALSE;
		}
	return TRUE;
}

//  If InstHit doesnt find it, then this function will check for an empty way and fill the instruction in there
int InstMiss(int set_index, int new_tag){
	Stats_Cache.cache_miss++; //increment miss
	for(int idc = 0; idc < INST_WAY; idc++){
		if(Inst_Cache[set_index][idc].mesi == I){
			UpdateMESI(set_index, idc, n);
			Inst_Cache[set_index][idc].tag = new_tag;
			Inst_Cache[set_index][idc].index = temp_index;
			Inst_Cache[set_index][idc].address = address;
			Inst_Cache[set_index][idc].b_offset = temp_offset;
			InstUpdateLRU(set_index, idc);
			if(mode == 1)
				printf("Read from L2    <0x%lx>\n", (long)address);
			return TRUE;
		}
		if(idc == INST_WAY -1)
			return FALSE;
	}
	return TRUE;
}

//  If there are no empty ways found in InstMiss, then evict the way that is LRU
void InstEvictLRU(int set_index, int new_tag){
	for (int idc= 0; idc<INST_WAY; idc++){
		if (Inst_Cache[set_index][idc].lru == 0){
			if(mode == 1)
				printf("Read from L2    <0x%lx>\n", (long)address);
			Inst_Cache[set_index][idc].tag = new_tag;
			Inst_Cache[set_index][idc].index = temp_index;
			Inst_Cache[set_index][idc].address = address;
			Inst_Cache[set_index][idc].b_offset = temp_offset;
			UpdateMESI(set_index, idc, n);
			InstUpdateLRU(set_index, idc);
			return;
		}
	}

}

/*
	Functions in the Inst Cache that aren't part of normal operations

*/

// Clears the entire instruction cache, changes MESI to I, and LRU to -1
void InstClear(void){
	for(int set_index = 0; set_index<SETS; set_index++){
		for(int idc = 0; idc<INST_WAY; idc++){
			Inst_Cache[set_index][idc].lru = -1; //decrement lru values 
			Inst_Cache[set_index][idc].mesi = I; //invalid 
		}
	}
}

// Prints all the contents of the instruction cache, provided that they are not Invalid
void PrintInstCache(void){
	printf("\n~~~~~~~~~~~~~ INST_CACHE ~~~~~~~~~~~~~\n");
	for(int index_set = 0; index_set < SETS; index_set++){
		for(int index_line = 0; index_line < INST_WAY; index_line++){
			if(Inst_Cache[index_set][index_line].mesi != I){
				printf("-----\n");
				printf("SET: %lx WAY: %d MESI: %d LRU: %d ADDRESS: %lx \n", 
					(long)Inst_Cache[index_set][index_line].index,
					index_line + 1,
					Inst_Cache[index_set][index_line].mesi,
					Inst_Cache[index_set][index_line].lru,
					(long)Inst_Cache[index_set][index_line].address);
			}
		}
	}	
	return;
}	
