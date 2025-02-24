import room_state::*;

module sword_machine (
    input logic clk,
    input logic reset,
    input room_state_type room,
    output logic founded_sword);

    typedef enum logic [2:0] {state_initial, state_founded} sword_state;
    sword_state current_state, next_state;

    always_ff @(posedge clk, posedge reset)
        if(reset) 
			current_state <= state_initial;
        else 
			current_state <= next_state;
    
    always_comb
        case (current_state)
        
            state_initial:
                if(room === r_3) 
						next_state = state_founded;
                else 
						next_state = state_initial;
            
            state_founded:
                next_state = state_founded;

        endcase
    
    assign founded_sword = (current_state == state_founded);

endmodule 