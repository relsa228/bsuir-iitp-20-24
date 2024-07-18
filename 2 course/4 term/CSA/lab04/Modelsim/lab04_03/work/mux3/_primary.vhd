library verilog;
use verilog.vl_types.all;
entity mux3 is
    generic(
        WIDTH           : integer := 8
    );
    port(
        d0              : in     vl_logic_vector;
        d1              : in     vl_logic_vector;
        d2              : in     vl_logic_vector;
        s               : in     vl_logic_vector(1 downto 0);
        y               : out    vl_logic_vector
    );
end mux3;
