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

#include <Instruction.h>

//TODO: add function files
//TODO: add 

//functions

int instruction_hit(int tag_value, int idx);
int instruction_miss(int tag_value, int idx);
int instruction_read(int tag_value, int idx);

void instruction_update_LRU(/*takes two parameters*/);
void instruction_evect_LRU(/*takes two parameters*/);
void instruction_inital_sate(void);
void instruction_statistics(/*no paramaters*/);


//exclusive, invalid... no mesi state