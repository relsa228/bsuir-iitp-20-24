library verilog;
use verilog.vl_types.all;
entity main_state_machine is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        op              : in     vl_logic_vector(6 downto 0);
        PCUpdate        : out    vl_logic;
        Branch          : out    vl_logic;
        RegWrite        : out    vl_logic;
        MemWrite        : out    vl_logic;
        IRWrite         : out    vl_logic;
        ALUSrcA         : out    vl_logic_vector(1 downto 0);
        ALUSrcB         : out    vl_logic_vector(1 downto 0);
        ResultSrc       : out    vl_logic_vector(1 downto 0);
        AdrSrc          : out    vl_logic;
        ALUOp           : out    vl_logic_vector(1 downto 0)
    );
end main_state_machine;
