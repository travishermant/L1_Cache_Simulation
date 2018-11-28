/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	Assuming the Hit and Miss operations will happen outside of this function
*/

#include "MESI.h"

int UpdateMESI(int set, int way, int n /* 'n' from trace file */){

	int check;
	
	if((n == 0) && (Data_Cache[set][way].mesi == I)){
	//Moving from invalid to exclusive
		Data_Cache[set][way].mesi = E;
		check = 0;
	}
	// Add transition for data eviction for miss
	else if((n == 0) && (Data_Cache[set][way].mesi == E) && (miss == TRUE)){
	//Moving from exclusive to shared, assuming other processor is reading
		Data_Cache[set][way].mesi = E;
		check = 0;
		miss = FALSE;
	}
	else if((n == 0) && (Data_Cache[set][way].mesi == E) && (miss == FALSE)){
	//If read command stay in shared state
		Data_Cache[set][way].mesi = S;
		check = 0;
		miss = FALSE;
	}
	else if((n == 1) && (Data_Cache[set][way].mesi == S)){
	//If write command and in shared state go to modified
		Data_Cache[set][way].mesi = M;
		check = 0;
	}
	else if((n == 1) && (Data_Cache[set][way].mesi == E)){
	//If write command and in the exclusive state go to modified
		Data_Cache[set][way].mesi = M;
		check = 0;
	}
	else if((n == 0 || n == 1) && (Data_Cache[set][way].mesi == M)){
	//Either read or write command, stay in modified state
		Data_Cache[set][way].mesi = M;
		check = 0;
	}
	else if(n == 4){
	//Response to snooping, data request from L2
		while(way < 8){
			if(Data_Cache[set][way].tag == temp_tag){
				if((Data_Cache[set][way].mesi == M) && (mode == 1))
					printf("Return data to L2    <0x%lx>\n", (long)address);
				Data_Cache[set][way].mesi = I;
				Data_UpdateLRU(set,way);
				return 0;
			}
			way++;
		}
		check = 0;
	}
	else if(n == 3){
	//Invalidate command from L2
		Data_Cache[set][way].mesi = I;
		check = 0;
	}
	else if(n == 2){
		Inst_Cache[set][way].mesi =  S; //??
		check = 0;
	}
	else
		check = 1;
	
//Returns 0 if successfully completed 
//Returns 1 if did not meet any statements, meaning error
return check;
}

