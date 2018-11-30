/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	LRU = 0, MRU = 7 for DATA CACHE
	LRU = 0, MRU = 3 for INSTRUCTION CACHE
*/

#include "LRU.h"

int InstUpdateLRU(int set, int way)
{
	int check = 0;
	int temp_way = 0;
	int prev_lru = 0;
	if(Inst_Cache[set][way].lru == INST_WAY - 1)
		Inst_Cache[set][way].lru = INST_WAY - 1;
	else if(Inst_Cache[set][way].lru >= 0){
		prev_lru = Inst_Cache[set][way].lru;
		for(int i = 0; i < INST_WAY; i++){ 
			if(Inst_Cache[set][i].lru > prev_lru)
				Inst_Cache[set][i].lru = (Inst_Cache[set][i].lru -1);		
		}
		Inst_Cache[set][way].lru = INST_WAY - 1;
		check = 0;
	}
	else if(Inst_Cache[set][way].lru == -1){
	// From initialized cache, so -1 means empty way
		Inst_Cache[set][way].lru = INST_WAY - 1;
		while(way > 0){
			--way;
			Inst_Cache[set][way].lru = (Inst_Cache[set][way].lru - 1);		
		}
		check = 0;
	}
	
return check;
}

int DataUpdateLRU(int set, int way)
{
	int check = 0;
	int temp_way = 0;
	int prev_lru = 0;
	if(Data_Cache[set][way].lru == DATA_WAY - 1)
		Data_Cache[set][way].lru = DATA_WAY - 1;
	else if(Data_Cache[set][way].lru >= 0){
		prev_lru = Data_Cache[set][way].lru;
		for(int i = 0; i < DATA_WAY; i++){ 
			if(Data_Cache[set][i].lru > prev_lru)
				Data_Cache[set][i].lru = (Data_Cache[set][i].lru -1);		
		}
		Data_Cache[set][way].lru = DATA_WAY - 1;
		check = 0;
	}
	else if(Data_Cache[set][way].lru == -1){
	// so -1 means empty way
		Data_Cache[set][way].lru = DATA_WAY - 1;
		while(way > 0){
			--way;
			Data_Cache[set][way].lru = (Data_Cache[set][way].lru - 1);	
		}
		check = 0;
	}
return check;
}
