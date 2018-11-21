/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	Assuming the Hit and Miss operations will happen outside of this function
*/

#include "MESI.h"
extern struct cache thecache;

int mesi_update(int set, int way, int n /* 'n' from trace file */){

	int check;
	
	if(thecache[set][way] == NULL){
	//Empty way set MESI as invalid
		thecache[set][way].mesi = 3;
		check = 0;
	}
	else if((n == 0) && (thecache[set][way].mesi == 3)){
	//Moving from invalid to exclusive
		thecache[set][way].mesi = 1;
		check = 0;
	}
	else if((n == 0) && (thecache[set][way].mesi == 1)){
	//Moving from exclusive to shared, assuming other processor is reading
		thecache[set][way].mesi = 2;
		check = 0;
	}
	else if((n == 0) && (thecache[set][way].mesi == 2)){
	//If read command stay in shared state
		thecache[set][way].mesi = 2;
		check = 0;
	}
	else if((n == 1) && (thecache[set][way].mesi == 2)){
	//If write command and in shared state go to modified
		thecache[set][way].mesi = 0;
		check = 0;
	}
	else if((n == 1) && (thecache[set][way].mesi == 1)){
	//If write command and in the exclusive state go to modified
		thecache[set][way].mesi = 0;
		check = 0;
	}
	else if((n == 0 || n == 1) && (thecache[set][way].mesi == 0)){
	//Either read or write command, stay in modified state
		thecache[set][way].mesi = 0;
		check = 0;
	}
	else
		check = 1;
	
//Returns 0 if successfully completed 
//Returns 1 if did not meet any statements, meaning error
return check;
}

