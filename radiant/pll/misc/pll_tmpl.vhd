component pll is
    port(outglobal_o: out std_logic;
         lock_o: out std_logic;
         outcore_o: out std_logic;
         ref_clk_i: in std_logic;
         rst_n_i: in std_logic);
end component;

__: pll port map(outglobal_o=> , lock_o=> , outcore_o=> , ref_clk_i=> ,
    rst_n_i=> );