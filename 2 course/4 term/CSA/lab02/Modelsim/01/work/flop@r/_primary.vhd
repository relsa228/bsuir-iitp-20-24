library verilog;
use verilog.vl_types.all;
entity flopR is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        d               : in     vl_logic_vector(5 downto 0);
        q               : out    vl_logic_vector(5 downto 0)
    );
end flopR;
