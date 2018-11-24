/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

-Instruction cache acts as a buffer memory between external memory 
and the processor.
-When code executes, instruction sets are copied into the Instruction 
Cache for direct access by the core processor
-instruction cache doesnt write 

Inst_Cache[SETS][INST_WAY] //our code
Instr_Cache[I_SETS][I_WAY] 

//MESI
#define	M				0
#define	E				1
#define	S				2
#define	I				3

*/

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <Instruction.h>

//TODO: add function files

int instruction_hit(int tag_value, int idx)
{
//increment the size of INST_WAY 
//per increment IF the conetent's struct memeber tag is equal to tag (other value thats passed in) 
//and the content's struct meber mesi is != to invalid state (3)

//upadte LRU by passing value of the the parameters passed into the instruction_hit function

//update LRU using vsalues obtained from instruction_hit


	int idc=1;
	int successfulFlag=1; 
//	int unsuccesfulFlag=0;
	for (idc;idc<INST_WAY;idc++)
	{
		if (Inst_Cache[idx][idc].tag == tag_value)
		{
			if (Inst_Cache[idx][idc].mesi != 3)
			{
				instruction_update_LRU(tag_value, idc);
				return successfulFlag; //no idea if any number thats not !=0 works
			}
			else if (Inst_Cache[idx][idc].mesi == 3)
			{
				printf("ERROR! invalid state cannot be hit");
			}
			/*
			else if (idx == INST_WAY)
			{
				print("ERROR! cache didnt contain the instruction");
				return unsuccesfulFlag; 
			}
			*/

		}
			return successfulFlag; //no idea if any number thats not !=0 works
		//this value is used by LRU evict
	}

}
int instruction_miss(int tag_value, int idx)
{
//increment the size of INST_WAY 

//per increment IF the conetent's struct memeber MESI is equal to 3 (invalid)

//update instructio cache by setting 

//Inst_Cache[passed in value][local variable used for FOR loop].mesi = 3

//update LRU by passing value fo the pararmenters paseed into Intruction_miss function
	int idc = 1;
	for (idc;idc<=INST_WAY;idc++)
	{
		if (Inst_Cache[idx][idc].mesi == 3)
		{
			Inst_Cache[idx][idc].tag = tag_value;
			Inst_Cache[idx][idc].mesi = 2;
			instruction_update_LRU(tag_value,idx);
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

}
int instruction_read(int tag_value, int idx)
{	
//check status or return values of instruction_hit AND instruction_miss are both !0
//call instruction_evect_LRU and pass it the parameters passed to this function

//if instruction_hit !0 and instruction_miss is 0, return 0
//else, return 1
	int unsuccessfulFlag=0;
	int successfulFlag=1; 
	if ((instruction_hit(int tag_value, int idx) == unsuccessfulFlag) && (instruction_miss(int tag_value, int idx)) == unsuccessfulFlag)
	{
		instruction_evect_LRU(int tag_value, int idx);
		printf("instruction evicted because there wasnt a hit nor a miss. instruction_read")
		return 0;
	}
	else
	{
		printf("ERROR! instruction_read cannot call evict because there was a hit or a miss")
	}
	return successfulFlag;
}

void instruction_update_LRU(int idx, int idc)
{
	//get current LRU
	int currentInstruction = Inst_Cache[idx][idc].lru;
	int temp_INST_WAY =1;
//check if Inst_Cache[parm1][parm2].LRU == 0
	//no need to change anything, return 0

// if Inst_Cache[parm1][parm2].LRU != 0
	// any LRU bit less than the current bit should get decremented/incremented depending on 
	// 00 for LRU or 11 for LRU

//check to see if instruction is currently the least recently used
//if so, do nothing
	if (Inst_Cache[idx][idc].lru == 0)
	{
		printf("LRU update was NOT required")
		return;
	}

	//if its not
	// anything less than current, increment
	// anything less than current, decrement
	else
	{
		printf("LRU update was required");
		for (temp_INST_WAY;temp_INST_WAY <= INST_WAY;temp_INST_WAY++)
		{
			//change values that are less than currentInstruction
			if (Inst_Cache[idx][idc].lru < currentInstruction)
			{
				//increment value
				Inst_Cache[idx][idc].lru++;
			}
		}

	}
	//return???
}

void instruction_evect_LRU(int tag_value, int idx)
{
//while parm2 is less than INST_WAY 
	//if ~[parm1][parm2].LRU == INST_WAY
		//~.tag = tag (parm2)
		//call instruction_update_LRU
	int idc=1;
	for (idc;idc<INST_WAY;idc++)
	{
		//check for equivalence between traversed value and testing value
		if (Inst_Cache[idx][idc].lru == INST_WAY)
		{
			//set new value
			Inst_Cache[idx][idc].tag = tag_value;
			//update LRU order
			instruction_update_LRU(tag_value,idx);
			return;
		}
		printf("ERROR! cant find testing value in the instruction cache. instruction_evect_LRU")
	}

}
void instruction_inital_sate(void)
{
	//statistics variables back to zero 
	int cache_read = 0, cache_write = 0, cache_hit = 0, cache_miss = 0;
	int idx = 0, idc = 0; //index
	//for loop to change all MESI back to invalid and reset LRU order back to inital order
	for (idx;idx<SETS;idx++)
	{
		for (idc;idc<INST_WAY;idc++)
		{
			Inst_Cache[idx][idc].lru = INST_WAY -1; //decrement lru values 
			Inst_Cache[idx][idc].mesi = 3; //invalid 
		}
	}
}

void instruction_statistics(/*no parameters*/)
{
	/*another file takes care of this??*/
}


//exclusive, invalid, shared ... no modified state