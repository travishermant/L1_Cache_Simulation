// 	ECE485
//	Travis Hermant, Alex Pinzon, Abdullah Barghouti, Ammar Khan
//	Testbench module
//	Parse through the file line by line, receive plusarg inputs to determine trace file and mode
//

// 	TODO:
//	Clocks, correct wires and registers
//	Info on reading files: https://stackoverflow.com/questions/16630319/how-to-read-a-text-file-line-by-line-in-verilog



module testbench;
	parameter CLOCK_CYCLE = 20;
	parameter CLOCK_WIDTH = CLOCK_CYCLE/2;
	parameter TRUE = 1'b1;
	parameter FALSE = 1'b0;	
	
	reg 		clock;
	int 		file;
	reg [99:0]	tracefile;
	reg [31:0]	address;
	reg [3:0]	instruction;
	
	//Create clock
	initial
	begin
		clock = FALSE;
		forever #CLOCK_WIDTH clock = ~clock;
	end
	
	
	initial
	begin
		if($value$plusargs("Trace_File=%s", tracefile) == FALSE)
		begin
			// do we want a default file selected if not declared?
			$display("No trace file selected");
			$finish;
		end
		
		if($value$plusargs("Mode=%d", mode) == TRUE)
		begin
			file = $fopen(tracefile, "r");
		end
	end
	
	always(@pos_edge clock)
	begin
		if(!feof(file))
			$fscanf(file, "%h\n", address);
		else
		begin
			$display("hit end of file");
			$fclose(file);
			$finish;
		end
	end
		
		
		//while(!$feof(file))
		//begin
			//$fscanf(file, "%h\n", address)
		//end
			
endmodule		