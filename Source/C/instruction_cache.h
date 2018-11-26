/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/
/*

-Instruction cache acts as a buffer memory between external memory 
and the processor.
-When code executes, instruction sets are copied into the Instruction 
Cache for direct access by the core processor
-instruction cache doesnt write 

Inst_Cache[SETS][INST_WAY]

*/
/*

-Instruction cache acts as a buffer memory between external memory 
and the processor.
-When code executes, instruction sets are copied into the Instruction 
Cache for direct access by the core processor
-instruction cache doesnt write 

Inst_Cache[SETS][INST_WAY]
*/

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <instruction_cache.h>
#include "main.h"
//TODO: add function files

//functions
int InstHit(int tag_value, int idx);
int InstMiss(int tag_value, int idx);
int InstRead(int tag_value, int idx);

//void InstUpdateLRU(int idx, int idc); LRU FILE TAKES CARE OF THIS
void InstEvictLRU(int tag_value, int idx);
void InstClear(void); 


//exclusive, invalid... no mesi state