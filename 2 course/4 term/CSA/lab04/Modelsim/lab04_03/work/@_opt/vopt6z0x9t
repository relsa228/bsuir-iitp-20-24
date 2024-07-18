library verilog;
use verilog.vl_types.all;
entity datapath is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        PCWrite         : in     vl_logic;
        AdrSrc          : in     vl_logic;
        Adr             : out    vl_logic_vector(31 downto 0);
        IRWrite         : in     vl_logic;
        ReadData        : in     vl_logic_vector(31 downto 0);
        Instr           : out    vl_logic_vector(31 downto 0);
        RegWrite        : in     vl_logic;
        ImmSrc          : in     vl_logic_vector(1 downto 0);
        ALUSrcA         : in     vl_logic_vector(1 downto 0);
        ALUSrcB         : in     vl_logic_vector(1 downto 0);
        ALUControl      : in     vl_logic_vector(2 downto 0);
        Zero            : out    vl_logic;
        ResultSrc       : in     vl_logic_vector(1 downto 0);
        WriteData       : out    vl_logic_vector(31 downto 0)
    );
end datapath;
