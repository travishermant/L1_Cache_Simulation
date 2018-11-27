/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

#include "statistics.h"

void ClearStats(){
	Stats_Cache.cache_read = 0;
	Stats_Cache.cache_write = 0;
	Stats_Cache.cache_hit = 0;
	Stats_Cache.cache_miss = 0;
return;
}

void PrintStats(){
	float ratio; 
	float total;
	
	total = Stats_Cache.cache_hit + Stats_Cache.cache_miss;
	ratio = Stats_Cache.cache_hit / total * 100; 
	
	printf("\n~~~~~~~~~~~~~ STATISTICS ~~~~~~~~~~~~~\n");
	printf("Number of cache reads: %d\n", Stats_Cache.cache_read);
	printf("Number of cache wrties: %d\n", Stats_Cache.cache_write);
	printf("Number of cache hits: %d\n", Stats_Cache.cache_hit);
	printf("Number of cache misses: %d\n", Stats_Cache.cache_miss);
	printf("Hit ratio percentage: %.2f %% \n", ratio);
return;	
}	

