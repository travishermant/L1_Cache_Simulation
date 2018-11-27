/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

-Instruction cache acts as a buffer memory between external memory 
and the processor.
-When code executes, instruction sets are copied into the Instruction 
Cache for direct access by the core processor
-instruction cache doesnt write 


//MESI
#define	M				0
#define	E				1
#define	S				2
#define	I				3

*/

#include "instruction_cache.h"

//int InstRead(int tag_value, int idx)
int InstRead(int set_index, int new_tag){	
	if(InstHit(new_tag,set_index) == FALSE){
		if(InstMiss(new_tag,set_index) == FALSE)	
			InstEvictLRU(new_tag,set_index);
		return FALSE;
	}
	return TRUE;
}

//int InstHit(int tag_value, int idx)
int InstHit(int set_index, int new_tag){
	for(int idc = 1; idc<INST_WAY; idc++){
		if(Inst_Cache[set_index][idc].tag == new_tag){
			if (Inst_Cache[set_index][idc].mesi != I){
				InstUpdateLRU(set_index, idc);
				Stats_Cache.cache_hit++; //increment hit counter
				return FALSE;
			}
			else if (Inst_Cache[set_index][idc].mesi == I)
				return FALSE;
		}
	}
	return TRUE;
}

//int InstMiss(int tag_value, int idx)
int InstMiss(int set_index, int new_tag){
	Stats_Cache.cache_miss++; //increment miss
	for(int idc = 1;idc<=INST_WAY;idc++){
		if (Inst_Cache[set_index][idc].mesi == I){
			Inst_Cache[set_index][idc].tag = new_tag;
			Inst_Cache[set_index][idc].index = temp_index;
			Inst_Cache[set_index][idc].address = address;
			Inst_Cache[set_index][idc].b_offset = temp_offset;
			UpdateMESI(set_index, idc, n);
			InstUpdateLRU(set_index, idc);
			return TRUE;
		}
		if(idc == INST_WAY -1)
			return FALSE;
	}
	return TRUE;
}

//void InstEvictLRU(int tag_value, int idx)
void InstEvictLRU(int set_index, int new_tag){
	for (int idc=1; idc<INST_WAY; idc++){
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

void InstClear(void){
	for(int set_index = 0; set_index<SETS; set_index++){
		for(int idc = 0; idc<INST_WAY; idc++){
			Inst_Cache[set_index][idc].lru = -1; //decrement lru values 
			Inst_Cache[set_index][idc].mesi = I; //invalid 
		}
	}
}


void PrintInstCache(void){
	printf("\n~~~~~~~~~~~~~ INST_CACHE ~~~~~~~~~~~~~\n");
	for(int index_set = 0; index_set < SETS; index_set++){
		for(int index_line = 0; index_line < INST_WAY; index_line++){
			if(Inst_Cache[index_set][index_line].mesi != I){
				printf("-----\n");
				printf("MESI: %d LRU: %d Address: %lx \n", 
					Inst_Cache[index_set][index_line].mesi,
					Inst_Cache[index_set][index_line].lru,
					(long)Inst_Cache[index_set][index_line].address);
			}
		}
	}	
}	
