library verilog;
use verilog.vl_types.all;
entity lab04_03 is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        MemWrite        : out    vl_logic;
        Adr             : out    vl_logic_vector(31 downto 0);
        WriteData       : out    vl_logic_vector(31 downto 0);
        ReadData        : in     vl_logic_vector(31 downto 0)
    );
end lab04_03;
