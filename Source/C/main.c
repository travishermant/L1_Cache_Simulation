/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan


*/

#include "main.h"
#include "statistics.h"
#include "instruction_cache.h"
#include "data_cache.h"

FILE 	*fp;				// file pointer
char 	*trace_file;		// temporary buffer for trace file name
char	trace_buffer[20];	// buffer for reading lines in tracefile
char	*token;				// Token for splitting the strings
long	buff[2];			// Buffer for converting from string to long
int		mode;				// 0 or 1, decides				
int		n;					// Trace "n" commands
uint32_t address, temp_tag, temp_index, temp_offset;
int 	i = 0;
int 	miss = FALSE;		// miss flag for data eviction

// Initialize the caches
struct stats	Stats_Cache;
struct cache	Inst_Cache[SETS][INST_WAY], Data_Cache[SETS][DATA_WAY];

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Mode and Trace File required \n Enter mode first and then file \n");
		printf("Mode is 0 or 1, filename format is '<file>.txt'\n");
		return -1;
	}
	else if(argc == 3){
		mode = atoi(argv[1]);
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
	InstClear();
	DataClear();
	
	//	Read through Trace File line by line
	while(fgets(trace_buffer, sizeof(trace_buffer), fp) != NULL){
		
		i = 0;
		token = strtok(trace_buffer, " ");
        while (token != NULL){
			buff[i] = (uint32_t) strtol(token, NULL, 16);
			i++;
			token = strtok(NULL, " ");
		}
		n = (int)buff[0];
		address = (uint32_t)buff[1];
		
		SplitAddress();
		
		switch(n){
			case L1_READ_DATA:
				// Data Cache Function
				Stats_Cache.cache_read++;
				DataRead(temp_index, temp_tag);
				break;
			case L1_WRITE_DATA:
				// Data Cache Function
				Stats_Cache.cache_write++;
				DataRead(temp_index, temp_tag);
				break;
			case L1_READ_INST:
				// Inst Cache Function
				Stats_Cache.cache_read++;
				InstRead(temp_index, temp_tag);
				break;
			case L2_INVALID:
				// Just a MESI function
				UpdateMESI(temp_index, 0, n);
				break;
			case L2_SNOOP_DATA:
				// Just a MESI function
				UpdateMESI(temp_index, 0, n);
				break;
			case RESET:
				// Both cache functions to reset
				InstClear();
				DataClear();
				// Stat function to clear all stats
				ClearStats();
				break;
			case PRINT:
				// Stat function to print
				PrintStats();
				// Printing the contents of all valid cache entries
				PrintInstCache();
				PrintDataCache();
				break;
			default:
				printf("Incorrect trace %s\n", trace_buffer);
				break;
		}
	}	
	fclose(fp);
	return 1;
}

void SplitAddress(){
	temp_tag = address >> 20;
	temp_index  = (address << 12) >> 18;
	temp_offset = (address << 26) >> 26;
}
