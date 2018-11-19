/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

#include "main.h"

FILE 	*fp;				// file pointer
char 	*trace_file;		// temporary buffer for trace file name
char	*trace_buffer[20];	// buffer for reading lines in tracefile
int		mode;				// 1 or 2, decides
int		trace;				//
int		n;					// Trace "n" commands
uint32_t address;


//Stat variables
int cache_read, cache_write = 0;
int cache_hit, cache_miss = 0;
float hit_ratio = 0;

struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Mode and Trace File required \n Enter mode first and then file \n");
		printf("Mode is 1 or 2, filename format is 'file.txt'\n");
		return -1;
	}
	else if(argc == 3){
		mode = stoi(argv[1]);
		trace_file = argv[2];
	}
	else{
		printf("ERROR");
		return -1;
	}
	
	// Opening the file
	fp = fopen(trace_file, "r");
	if(!fp){
		printf("Opening file failed, quitting...\n");
		return -1;
	}
	//	Initialize caches
	
	
	//	Read through Trace File line by line
	while(fgets(trace_buffer, 20, fp) != NULL){
		n = trace_buffer[0];
		
		
		
		
		
	
	
	
	
	
	}
	
	
	
	
	
	
	
	fclose(fp);
}