/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

#include "main.h"

extern struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];
extern int	mode, miss;
extern uint32_t address;

int UpdateMESI(int set, int way, int n);
