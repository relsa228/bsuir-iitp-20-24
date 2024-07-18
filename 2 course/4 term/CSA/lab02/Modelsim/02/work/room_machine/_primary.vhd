library verilog;
use verilog.vl_types.all;
entity room_machine is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        north           : in     vl_logic;
        south           : in     vl_logic;
        west            : in     vl_logic;
        east            : in     vl_logic;
        sword_founded   : in     vl_logic;
        room            : out    work.room_state.room_state_type
    );
end room_machine;
