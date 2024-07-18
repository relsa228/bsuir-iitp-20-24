module testbench ();

   logic clk, reset;
	logic north, south, west, east, win, die;
    logic [1:0] global_result;
	logic [31:0] vectornum, errors;
	logic [6:0] testvectors[10000:0];
	logic global_reset;
    
    lab02_02 dut(clk, reset, north, south, west, east, win, die);
    always
        begin
            clk = 1; #5;
            clk = 0; #5;
        end
    
    initial
        begin
            $readmemb("lab02_02.tv", testvectors);
            vectornum = 0; errors = 0; reset = 1; #22; reset = 0;
        end
    
    always @(posedge clk)
        begin
            #1; {global_reset, north, south, west, east, global_result} = testvectors[vectornum];
            if(global_reset) begin
                reset = 1;
                #22;
                reset = 0;
            end
        end
    
    always @(negedge clk)
        if(~reset) begin
            if({win, die} !== global_result) begin
                $display("Test %d -- crush \n", vectornum);
                $display("Error: inputs = %b", {reset, north, south, west, east});
				$display(" outputs = %b %b (%b expected)", win, die, global_result);
				errors = errors + 1;
            end
            else if(global_result === 2'b10) begin
                $display("God bless you, hero.");
            end
            else if(global_result === 2'b01) begin
                $display("With this character's death, the thread of prophecy is severed. Restore a saved game to restore the weave of... just a joke, we don't have saves.");
            end
            vectornum = vectornum + 1;
			if(testvectors[vectornum] === 7'bx) begin
				$display("%d tests completed with %d errors", vectornum, errors);
				$stop;
            end
        end

endmodule 