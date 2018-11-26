/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	Assuming the Hit and Miss operations will happen outside of this function
*/

#include "MESI.h"
extern struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];

int UpdateMESI(int set, int way, int n /* 'n' from trace file */){

	int check;
	
	if((n == 0) && (Data_Cache[SETS][DATA_WAY].mesi == 3)){
	//Moving from invalid to exclusive
		Data_Cache[SETS][DATA_WAY].mesi = 1;
		check = 0;
	}
	else if((n == 0) && (Data_Cache[SETS][DATA_WAY].mesi == 1)){
	//Moving from exclusive to shared, assuming other processor is reading
		Data_Cache[SETS][DATA_WAY].mesi = 2;
		check = 0;
	}
	else if((n == 0) && (Data_Cache[SETS][DATA_WAY].mesi == 2)){
	//If read command stay in shared state
		Data_Cache[SETS][DATA_WAY].mesi = 2;
		check = 0;
	}
	else if((n == 1) && (Data_Cache[SETS][DATA_WAY].mesi == 2)){
	//If write command and in shared state go to modified
		Data_Cache[SETS][DATA_WAY].mesi = 0;
		check = 0;
	}
	else if((n == 1) && (Data_Cache[SETS][DATA_WAY].mesi == 1)){
	//If write command and in the exclusive state go to modified
		Data_Cache[SETS][DATA_WAY].mesi = 0;
		check = 0;
	}
	else if((n == 0 || n == 1) && (Data_Cache[SETS][DATA_WAY].mesi == 0)){
	//Either read or write command, stay in modified state
		Data_Cache[SETS][DATA_WAY].mesi = 0;
		check = 0;
	}
	else if((n == 4) && Data_Cache[SETS][DATA_WAY] != 3){
	//Response to snooping, data request from L2
		Data_Cache[SETS][DATA_WAY].mesi = 2;
		check = 0;
	}
	else if(n == 3){
	//Invalidate command from L2
		Data_Cache[SETS][DATA_WAY].mesi = 3;
		check = 0;
	}
	else
		check = 1;
	
//Returns 0 if successfully completed 
//Returns 1 if did not meet any statements, meaning error
return check;
}

