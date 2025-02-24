module testbench();
	logic clk, reset;

	logic a, b, cin, s, cout, sexpected, coutexpected;
	logic [31:0] vectornum, errors;
	logic [4:0] testvectors[10000:0];
fulladder dut(a, b, cin, s, cout);
always

	begin
		clk=1; #5; 
		clk=0; #5;
	end

initial

	begin
		$readmemb("fulladder.tv", testvectors);
		vectornum=0; 
		errors=0;
		reset=1; #22;
		reset=0;
	end

always @(posedge clk)
	begin
		#1;
		{a,b,cin, coutexpected,sexpected} = testvectors[vectornum];
	end

always @(negedge clk)

	if (~reset) begin
		if (s !== sexpected || cout !== coutexpected) begin
			$display("Error: inputs = %b", {a, b, cin});
			$display(" outputs = %b %b (%b %b expected)", s, cout, sexpected, coutexpected);
			errors = errors + 1;
		end

		vectornum = vectornum + 1;

		if (testvectors[vectornum] === 5'bx) begin
			$display("%d tests completed with %d errors", vectornum, errors);
		$stop;
		end
	end
endmodule

