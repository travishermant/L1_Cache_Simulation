/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

#include "main.h"

extern struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];

//Prototypes
int InstUpdateLRU(int set ,int way);  //Use struct cache variables
int DataUpdateLRU(int set ,int way);  //Use struct cache variables
