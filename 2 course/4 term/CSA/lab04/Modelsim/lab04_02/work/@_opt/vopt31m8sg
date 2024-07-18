library verilog;
use verilog.vl_types.all;
entity lab04_02 is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        op              : in     work.lab04_02_sv_unit.opcodetype;
        funct3          : in     vl_logic_vector(2 downto 0);
        funct7b5        : in     vl_logic;
        Zero            : in     vl_logic;
        ImmSrc          : out    vl_logic_vector(1 downto 0);
        ALUSrcA         : out    vl_logic_vector(1 downto 0);
        ALUSrcB         : out    vl_logic_vector(1 downto 0);
        ResultSrc       : out    vl_logic_vector(1 downto 0);
        AdrSrc          : out    vl_logic;
        ALUControl      : out    vl_logic_vector(2 downto 0);
        IRWrite         : out    vl_logic;
        PCWrite         : out    vl_logic;
        RegWrite        : out    vl_logic;
        MemWrite        : out    vl_logic
    );
end lab04_02;
