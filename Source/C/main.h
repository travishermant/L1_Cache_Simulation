/*
	ECE 485
	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan

	Most parameters and defines will be handled here
*/


void SplitAddress();

#ifndef _GENERAL
#define _GENERAL

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>
#include	<math.h>
#include	<string.h>
//#include	<iostream>

#define FALSE			0
#define TRUE			1

#define	KILO			1024
#define MEGA			(KILO * KILO)

//Address information
#define	SETS			(16 * KILO)
#define	ADDRESS			32
#define	LINE			64
#define	TAG				12
#define	INDEX			14
#define	BYTE_OFFSET		6
#define	INST_WAY		4
#define	DATA_WAY		8

//Trace File Format
//	Where n is:			n
#define	L1_READ_DATA	0	// read data request to L1 data cache
#define	L1_WRITE_DATA	1	// write data request to L1 data cache
#define	L1_READ_INST	2	// instruction fetch (a read request to L1 instruction cache)
#define	L2_INVALID		3	// invalidate command from L2
#define	L2_SNOOP_DATA	4	// data request from L2 (in response to snoop)
#define	RESET			8	// clear the cache and reset all state (and statistics)
#define	PRINT			9	// print contents and state of the cache (allow subsequent trace activity)

//MESI
#define	M				0
#define	E				1
#define	S				2
#define	I				3

struct cache{
	int mesi;
	int lru;
	uint32_t address;
	uint32_t tag;
	uint32_t index;
	uint32_t b_offset;
};

struct stats{
	int cache_read, cache_write, cache_hit, cache_miss;	
};	


#endif