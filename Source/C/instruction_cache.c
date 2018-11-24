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
	int idc = 0;
	for (idc;idc<INST_WAY;idc++)
	{
		if (Inst_Cache[idx][idc].mesi == 3)
		{
			Inst_Cache[idx][idc].tag = tag_value;
			Inst_Cache[idx][idc].mesi = 2;
			instruction_update_LRU(tag_value,idx);
		}
		else if (idc==(INST_WAY-1))
		{
			return 0;
			printf("idc==INST_WAY-1");
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

void instruction_update_LRU(/*takes two parameters*/)
{
//check if Inst_Cache[parm1][parm2].LRU == 0
	//no need to change anything, return 0

// if Inst_Cache[parm1][parm2].LRU != 0
	// any LRU bit less than the current bit should get decremented/incremented depending on 
	// 00 for LRU or 11 for LRU

//int current = Inst_Cache[parm1][parm2].LRU;
// Inst_Cache[parm1][parm2].LRU = 0
// anything less tahn current, increment
// anything less than current, decrement

if (Inst_Cache)
}
void instruction_evect_LRU()
{
//while parm2 is less than INST_WAY -1, 
	//if ~[parm1][parm2].LRU == INST_WAY -1 
		//~.tag = tag (parm2)
		//call instruction_update_LRU


}
void instruction_inital_sate(void)
{
	//statistics variables back to zero 
	int cache_read = 0, cache_write = 0, cache_hit = 0, cache_miss = 0;	
	//for loop to change all MESI back to invalid and reset LRU order back to inital order
}

void instruction_statistics(/*no parameters*/)
{
	/*another file takes care of this??*/
}


//exclusive, invalid, shared ... no modified state