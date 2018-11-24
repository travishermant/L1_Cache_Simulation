/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

extern struct stats Stats_Cache;

void ClearStats(){
	Stats_Cache.cache_read,
	Stats_Cache.cache_write,
	Stats_Cache.cache_hit,
	Stats_Cache.cache_miss = 0;
return;
}

void PrintStats(){
	float ratio; 
	int total;
	
	total = Stats_Cache.cache_hit + Stats_Cache.cache_miss;
	ratio = (Stats_Cache.cache_hit / total) * 100; 
	
	printf("~~~~~~~~~~~~~ STATISTICS ~~~~~~~~~~~~~\n");
	printf("Number of cache reads: %d\n", Stats_Cache.cache_read);
	printf("Number of cache wrties: %d\n", Stats_Cache.cache_write);
	printf("Number of cache hits: %d\n", Stats_Cache.cache_hit);
	printf("Number of cache misses: %d\n", Stats_Cache.cache_miss);
	printf("Hit ratio percentage: %f %\n", ratio);
return;	
}	