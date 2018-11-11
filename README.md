# L1_Cache_Simulation

Design project for ECE485 at Portland State University

#	Team Members

Abdullah Barghouti

Travis Hermant

Ammar Khan

Alex Pinzon

# Split Cache Specs

32-bit processor

8-way Set Associative Data Cache and 4-way Set Associative Instruction Cache

16K sets (14 bits for index)

64-byte Cache line (6 bits for byte offset)

MESI Protocol


# Trace file format
## N Address
0. Read data request to L1 data cache
1. Write data request to L1 data cache
2. Instructions fetch (a read request to L1 instruction cache)
3. Invalidate command from L2
4. Data request from L2 (in response to snoop)
8. Clear the cache and reset all state (and statistics)
9. Print contents and state of the cache (allow subsequent trace activity)

# Modes
## Mode 1
Simulation displays only the required summary of usage statistics
and responses to 9s in the trace file and nothing else
## Mode 2
Simulation should display everything from mode 0 but also display the communication
messages to the L2 described above (and nothing else)


