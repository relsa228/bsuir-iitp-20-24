import room_state::*;

module lab02_02(
    input logic clk,
    input logic reset,
    input logic north, south, west, east,
    output logic win, die);

    logic sword_founded;
    room_state_type current_room;

    room_machine room_state_machine_var(clk, reset, north, south, west, east, sword_founded, current_room);
    sword_machine sword_state_machine_var(clk, reset, current_room, sword_founded);

    assign win = (current_room === r_6);
    assign die = (current_room === r_5);
    
endmodule 