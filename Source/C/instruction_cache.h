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
#include <unistd.h>
#include "main.h"
#include "LRU.h"
#include "MESI.h"

// Global variables
extern uint32_t address, temp_tag, temp_index, temp_offset;
extern int	mode, n;	
extern struct cache Inst_Cache[SETS][INST_WAY];
extern struct stats Stats_Cache;

//functions
int InstHit(int set_index, int new_tag);
int InstMiss(int set_index, int new_tag);
int InstRead(int set_index, int new_tag);
void InstEvictLRU(int set_index, int new_tag);
void InstClear(void); 
void PrintInstCache(void);