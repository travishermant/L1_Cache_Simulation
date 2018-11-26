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

//libraries 

#include "instruction_cache.h"
#include "LRU.h"
extern struct cache Inst_Cache[SETS][INST_WAY];


extern struct stats Stats_Cache;







int InstHit(int tag_value, int idx)
{
//increment the size of INST_WAY 
//per increment IF the conetent's struct memeber tag is equal to tag (other value thats passed in) 
//and the content's struct meber mesi is != to invalid state (3)

//upadte LRU by passing value of the the parameters passed into the instruction_hit function

//update LRU using vsalues obtained from instruction_hit

	//int idc=1;
	for (int idc = 1; idc<INST_WAY; idc++)
	{
		if (Inst_Cache[idx][idc].tag == tag_value)
		{
			if (Inst_Cache[idx][idc].mesi != I)
			{
				InstUpdateLRU(idx, idc);
				return TRUE; //no idea if any number thats not !=0 works
			}
			else if (Inst_Cache[idx][idc].mesi == I)
			{
				printf("ERROR! invalid state cannot be hit");
				return FALSE;
			}
			/*
			else if (idx == INST_WAY)
			{
				print("ERROR! cache didnt contain the instruction");
				return unsuccesfulFlag; 
			}
			*/

		}
			return TRUE; //no idea if any number thats not !=0 works
		//this value is used by LRU evict
	}
	return FALSE;

}
int InstMiss(int tag_value, int idx)
{
//increment the size of INST_WAY 
//per increment IF the conetent's struct memeber MESI is equal to 3 (invalid)
//update instructio cache by setting 
//Inst_Cache[passed in value][local variable used for FOR loop].mesi = 3
//update LRU by passing value fo the pararmenters paseed into Intruction_miss function
	//int idc = 1;
	for (int idc = 1;idc<=INST_WAY;idc++)
	{
		if (Inst_Cache[idx][idc].mesi == I)
		{
			// Update MESI here?
			Inst_Cache[idx][idc].tag = tag_value;
			Inst_Cache[idx][idc].index = temp_index;
			Inst_Cache[idx][idc].address = address;
			Inst_Cache[idx][idc].b_offset = temp_offset;
			UpdateMESI(idx, idx, n);
			InstUpdateLRU(idx, idc);
		}
		else if (idc==(INST_WAY))
		{
			return 0;
			printf("ERROR! traverse whole cache. instruction_miss");
		}
		//ONLY FOR TESTING
		else
		{
			printf("ERROR! occurred in instruction_hit");
		} 
	}
	return FALSE;
}
int InstRead(int tag_value, int idx)
{	
//check status or return values of instruction_hit AND instruction_miss are both !0
//call instruction_evect_LRU and pass it the parameters passed to this function

//if instruction_hit !0 and instruction_miss is 0, return 0
//else, return 1
	if (InstHit(tag_value,idx) == FALSE){
		if (InstMiss(tag_value,idx)) == FALSE)	
			InstEvictLRU(tag_value,idx);
		return 0;
	}
	return TRUE;
}


void InstEvictLRU(int tag_value, int idx)
{
//while parm2 is less than INST_WAY 
	//if ~[parm1][parm2].LRU == INST_WAY
		//~.tag = tag (parm2)
		//call instruction_update_LRU
	//int idc=1;
	for (int idc=1; idc<INST_WAY; idc++)
	{
		//check for equivalence between traversed value and testing value
		if (Inst_Cache[idx][idc].lru == INST_WAY - 1)
		{
			//set new value
			Inst_Cache[idx][idc].tag = tag_value;
			//update LRU order
			InstUpdateLRU(idx,idc);
			return;
		}
		printf("ERROR! cant find testing value in the instruction cache. instruction_evect_LRU");
	}

}

void InstClear(void)
{
	//statistics variables back to zero 
	//int cache_read = 0, cache_write = 0, cache_hit = 0, cache_miss = 0;
//	int idx = 0, idc = 0; //index
	//for loop to change all MESI back to invalid and reset LRU order back to inital order
	for(int idx = 0; idx<SETS; idx++)
	{
		for(int idc = 0; idc<INST_WAY; idc++)
		{
			Inst_Cache[idx][idc].lru = -1; //decrement lru values 
			Inst_Cache[idx][idc].mesi = I; //invalid 
		}
	}
}



//exclusive, invalid, shared ... no modified state



//~~~~~~~~ CACHE CLEAR FUNCTION NEEDED