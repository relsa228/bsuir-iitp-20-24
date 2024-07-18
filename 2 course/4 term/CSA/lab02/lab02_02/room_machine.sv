import room_state::*;

module room_machine(
    input logic clk,
    input logic reset,
    input logic north, south, west, east,
    input logic sword_founded,
    output room_state_type room);

    room_state_type current_state, next_state;

    always_ff @( posedge clk, posedge reset )
        if(reset) 
			current_state <= r_0;
        else 
			current_state <= next_state;

	 
		  
    always_comb
	 begin
	 next_state = current_state;
        case(current_state)
        
            r_0:
                if(east) 
						next_state = r_1;
                else 
						next_state = r_0;

            r_1:
                if(west) 
						next_state = r_0;
                else if(south) 
						next_state = r_2;
					 else 
						next_state = r_1;

            r_2:
                if(north) 
						next_state = r_1;
                else if(west) 
						next_state = r_3;
                else if(south) 
						next_state = r_7;
                else if(east) 
						next_state = r_4;

            r_3:
                if(east) 
						next_state = r_2;
					 else 
						next_state = r_3;

            r_4:
                if(sword_founded === 0 && east) 
						next_state = r_5;
                else if(sword_founded === 1 && east) 
						next_state = r_6;
					 else if(west) 
						next_state = r_2;
					 else 
						next_state = r_4;
					 
				r_5:
					 next_state = r_5;
					 
				r_6:
					 next_state = r_6;

            r_7:
                if(north) 
						next_state = r_2;
					 else if(east) 
						next_state = r_5;
					 else 
						next_state = r_7;

            default:
                next_state = r_0;

        endcase
	 end

    assign room = current_state;

endmodule 