library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DIVUCoreAndMemory is
    PORT (
        in0 : IN std_logic_vector(31 DOWNTO 0);
        in1 : IN std_logic_vector(31 DOWNTO 0);
        in2 : IN std_logic_vector(31 DOWNTO 0);
    
        out0 : OUT std_logic_vector(31 DOWNTO 0);
        out1 : OUT std_logic_vector(31 DOWNTO 0);
        out2 : OUT std_logic_vector(31 DOWNTO 0);
        
        frame_pointer : IN std_logic_vector(31 DOWNTO 0);
        frame_pointer_out : OUT std_logic_vector(31 DOWNTO 0);
        rst : IN std_logic; 
        clck  : IN std_logic; 
        
        mem_wait : IN std_logic;
        mem_push  : IN std_logic_vector(31 DOWNTO 0)
        );
        
end DIVUCoreAndMemory;

architecture Structure of DIVUCoreAndMemory is

component GreenDroidDIVUCore
     PORT (
       i00 : IN std_logic_vector(31 DOWNTO 0);
       i01 : IN std_logic_vector(31 DOWNTO 0);
       i02 : IN std_logic_vector(31 DOWNTO 0);

       r00 : OUT std_logic_vector(31 DOWNTO 0);
       r01 : OUT std_logic_vector(31 DOWNTO 0);
       r02 : OUT std_logic_vector(31 DOWNTO 0);

FP : IN std_logic_vector(31 DOWNTO 0);
FPout : OUT std_logic_vector(31 DOWNTO 0);
       M_ADDR :   OUT std_logic_vector(31 DOWNTO 0);
       M_DATA : INOUT std_logic_vector(31 DOWNTO 0);
       M_RD  : INOUT std_logic; 
       M_WR  : INOUT std_logic; 
       M_RDY : IN std_logic; 
       reset : IN std_logic; 
       CLK  : IN std_logic 
     ); 
 end component;
 
 component mem
   PORT (
         M_ADDR :   IN std_logic_vector(31 DOWNTO 0);
         M_DATA : INOUT std_logic_vector(31 DOWNTO 0);
         M_RD  : IN std_logic; 
         M_WR  : IN std_logic; 
         M_RDY : OUT std_logic;
          
     MWAIT : IN std_logic;
     MDAT  : IN std_logic_vector(31 DOWNTO 0)
       ); 
 end component;

signal sig_M_ADDR, sig_M_DATA : std_logic_vector(31 DOWNTO 0);
signal sig_M_RD, sig_M_WR, sig_M_RDY : std_logic;

begin
    Core: GreenDroidDIVUCore
    port map (
               i00 => in0, i01 => in1, i02 => in2,
               r00 => out0, r01 => out1, r02 => out2,
       
               FP => frame_pointer, FPout => frame_pointer_out,
               M_ADDR => sig_M_ADDR,
               M_DATA => sig_M_DATA,
               M_RD  => sig_M_RD,
               M_WR  => sig_M_WR,
               M_RDY => sig_M_RDY,
               reset => rst,
               CLK  => clck
               );
               
    mymem: mem
            port map(
            M_ADDR => sig_M_ADDR,
            M_DATA => sig_M_DATA,
            M_RD  => sig_M_RD,
            M_WR  => sig_M_WR,
            M_RDY => sig_M_RDY,
            MWAIT => mem_wait,
            MDAT  => mem_push
            );
            
end Structure;
