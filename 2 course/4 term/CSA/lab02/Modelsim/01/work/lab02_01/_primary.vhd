library verilog;
use verilog.vl_types.all;
entity lab02_01 is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        left            : in     vl_logic;
        right           : in     vl_logic;
        la              : out    vl_logic;
        lb              : out    vl_logic;
        lc              : out    vl_logic;
        ra              : out    vl_logic;
        rb              : out    vl_logic;
        rc              : out    vl_logic
    );
end lab02_01;
