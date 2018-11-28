/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
	This is the top level for the program, it will take in runtime commands for mode and input file, and then parse through the files
		line by line. It separates the command from the address, and divides the address into its appropriate conventions as decimal numbers
		Those decimal numbers are stored as global temp uint32_t's, and then functions are called in the caches to check for htis and misses
		and make the appropriate modifications.
		
        runtime  ---    Main.c   --- input.txt
                    /            \
                   /              \
           Inst_Cache             Data_Cache
           /    |    \           /    |     \
        MESI    |    LRU       MESI   |     LRU
                | 					  |	
              Stats                 Stats
		
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
// Stats Cache just stores various statistics to be called and printed at the end
struct stats	Stats_Cache;
// Both Inst_Cache and Data_Cache are set to be 2D arrays, with the same number of ways (16K) and 4 ways/8 ways per set, respectively
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
	//	Initialize caches; set all MESI to I, set all LRU to -1 
	InstClear();
	DataClear();
	
	//	Read through Trace File line by line, until there's nothing left
	while(fgets(trace_buffer, sizeof(trace_buffer), fp) != NULL){
		// Each line is a space " " separated string, so separate the string for each chunk
		i = 0;
		token = strtok(trace_buffer, " ");
        while (token != NULL){
			buff[i] = (uint32_t) strtol(token, NULL, 16);
			i++;
			token = strtok(NULL, " ");
		}
		// Store the separated chunks (tokens/whatever) into global variables
		n = (int)buff[0];
		address = (uint32_t)buff[1];
		
		SplitAddress();
		
		// n refers to the command found in the tracefile, check main.h for the defines and given description
		switch(n){
			case L1_READ_DATA:
				Stats_Cache.cache_read++;
				DataRead(temp_index, temp_tag);
				break;
			case L1_WRITE_DATA:
				// Call to write data, checking to see if it's held
				Stats_Cache.cache_write++;
				DataRead(temp_index, temp_tag);
				break;
			case L1_READ_INST:
				// Call for the instruction cache to read an instruction
				Stats_Cache.cache_read++;
				InstRead(temp_index, temp_tag);
				break;
			case L2_INVALID:
				// Occurs after a snoop, L2 sends a command to invalidate once other processor receives data
				UpdateMESI(temp_index, 0, n);
				break;
			case L2_SNOOP_DATA:
				// L2 is checking to see if L1 has other data that a different processor is looking for
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
				// Printing the contents of all valid (MESI != I) cache entries
				PrintInstCache();
				PrintDataCache();
				break;
			default:
				// Command was not 0,1,2,3,4,8,9
				printf("Incorrect trace %s\n", trace_buffer);
				break;
		}
	}	
	fclose(fp);
	return 1;
}

//		Address can be left and right shifted corresponding to the number of bits to isolate that area
//		[               Address 32-bits                   ]
//		[ Tag 12-bits | Index 14-bits | Byte Offset 6-bits]
void SplitAddress(){
	temp_tag = address >> 20;
	temp_index  = (address << 12) >> 18;
	temp_offset = (address << 26) >> 26;
}
