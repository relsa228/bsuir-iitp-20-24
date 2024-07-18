module flopR(input logic clk,
				 input logic reset,
				 input logic [5:0] d,
				 output logic [5:0] q);
				 
	always_ff @(posedge clk)
		if(reset) 
			q <= 6'b0;
		else 
			q <= d;
endmodule



module lab02_01 (input logic clk,
								  input logic reset,
								  input logic left, right,
								  output logic la, lb, lc, ra, rb, rc);
	
	logic [5:0] current_state, next_state;
	
	logic not_state_5, not_state_4, not_state_3, not_state_2, not_state_1, not_state_0, not_left, not_right;
	
	flopR flop(clk, reset, next_state, current_state);
	
	not n5(not_state_5, current_state[5]);
	not n4(not_state_4, current_state[4]);
	not n3(not_state_3, current_state[3]);
	not n2(not_state_2, current_state[2]);
	not n1(not_state_1, current_state[1]);
	not n0(not_state_0, current_state[0]);
	
	not nl(not_left, left);
	not nr(not_right, right);
	
	and a1(next_state[0], not_state_5, not_state_4, not_state_3, not_state_2, not_state_1, not_state_0, left, not_right);
	
	assign next_state[1] = current_state[0];
	assign next_state[2] = current_state[1];
	
	and a2(next_state[3], not_state_5, not_state_4, not_state_3, not_state_2, not_state_1, not_state_0, not_left, right);
	
	assign next_state[4] = current_state[3];
	assign next_state[5] = current_state[4];
	
	assign la = current_state[1] || current_state[2];
	assign lb = current_state[0] || current_state[2];
	assign lc = current_state[1] || current_state[2];
	assign ra = current_state[4] || current_state[5];
	assign rb = current_state[3] || current_state[5];
	assign rc = current_state[4] || current_state[5];
	
		
endmodule 