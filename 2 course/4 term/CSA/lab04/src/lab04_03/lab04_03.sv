typedef enum logic[6:0] {r_type_op=7'b0110011, i_type_alu_op=7'b0010011, lw_op=7'b0000011, sw_op=7'b0100011, beq_op=7'b1100011, jal_op=7'b1101111} opcodetype;

module testbench();

	logic        clk;
	logic        reset;

	logic [31:0] WriteData, DataAdr;
	logic        MemWrite;
	logic [31:0] hash;

	// instantiate device to be tested
	top dut(clk, reset, WriteData, DataAdr, MemWrite);
  
	// initialize test
	initial
		begin
			hash  <= 0;
			reset <= 1; # 22; reset <= 0;
		end

	// generate clock to sequence tests
	always
		begin
			clk <= 1; # 5; clk <= 0; # 5;
		end

	// check results
	always @(negedge clk)
		begin
			if(MemWrite) begin
				//$display("DataAdr:  ", DataAdr);
				//$display("WriteData:", WriteData);
				if(DataAdr === 100 & WriteData === 25) begin
					$display("Simulation succeeded");
					$display("hash = %h", hash);
					$stop;
				end else if (DataAdr !== 96) begin
					$display("Simulation failed");
					$stop;
				end
			end
		end

	// Make 32-bit hash of instruction, PC, ALU
	always @(negedge clk)
		if (~reset) begin
			hash = hash ^ dut.rvmulti.dp.Instr ^ dut.rvmulti.dp.PC;
			if (MemWrite) hash = hash ^ WriteData;
			hash = {hash[30:0], hash[9] ^ hash[29] ^ hash[30] ^ hash[31]};
		end

endmodule 

///////////////////////////////////////////////////////////////
// top
//
// Instantiates multicycle RISC-V processor and memory
///////////////////////////////////////////////////////////////

module top(input  logic        clk, reset, 
           output logic [31:0] WriteData, DataAdr, 
           output logic        MemWrite);

	logic [31:0] ReadData;
  
	// instantiate processor and memories
	lab04_03 rvmulti(clk, reset, MemWrite, DataAdr, 
                      WriteData, ReadData);
							 
	mem mem(clk, MemWrite, DataAdr, WriteData, ReadData);
	
endmodule

///////////////////////////////////////////////////////////////
// mem
//
// Single-ported RAM with read and write ports
// Initialized with machine language program
///////////////////////////////////////////////////////////////

module mem(input  logic        clk, we,
           input  logic [31:0] a, wd,
           output logic [31:0] rd);

	logic [31:0] RAM[63:0];
  
	initial
		$readmemh("riscvtest.txt",RAM);

	assign rd = RAM[a[31:2]]; // выравнивание на слово

	always_ff @(posedge clk)
		if (we) RAM[a[31:2]] <= wd;
		
endmodule

///////////////////////////////////////////////////////////////
// riscvmulti
//
// Multicycle RISC-V microprocessor
///////////////////////////////////////////////////////////////

module lab04_03(input  logic        clk, reset,
                  output logic        MemWrite,
                  output logic [31:0] Adr, WriteData,
                  input  logic [31:0] ReadData);
						
	logic 		 AdrSrc, PCWrite, IRWrite, RegWrite, Zero;
	logic [31:0] Instr;
	logic [1:0]  ImmSrc, ALUSrcA, ALUSrcB, ResultSrc;
	logic [2:0]  ALUControl;

	controller c(clk, reset, 
				    Instr[6:0], Instr[14:12], Instr[30], Zero,
				    ImmSrc, ALUSrcA, ALUSrcB, ResultSrc,
					 AdrSrc, ALUControl, 
					 IRWrite, PCWrite, RegWrite, MemWrite);
	
	datapath dp(clk, reset,
					PCWrite, AdrSrc, Adr, IRWrite,
               ReadData, Instr, RegWrite,
               ImmSrc, ALUSrcA, ALUSrcB, ALUControl, 
					Zero, ResultSrc, WriteData);

endmodule


// устройство управления (2)
module controller(input  logic       clk,
                  input  logic       reset,  
                  input  logic [6:0] op,
                  input  logic [2:0] funct3,
                  input  logic       funct7b5,
                  input  logic       Zero,
                  output logic [1:0] ImmSrc,
                  output logic [1:0] ALUSrcA, ALUSrcB,
                  output logic [1:0] ResultSrc, 
                  output logic       AdrSrc,
                  output logic [2:0] ALUControl,
                  output logic       IRWrite, PCWrite, 
                  output logic       RegWrite, MemWrite);

    logic [1:0] ALUOp;
    logic       Branch, PCUpdate;

    main_state_machine msm(clk, reset, op, PCUpdate, Branch, RegWrite, MemWrite,
									IRWrite, ALUSrcA, ALUSrcB, ResultSrc, AdrSrc, ALUOp);

	 instrdec id(op, ImmSrc);
									
    aludec ad(op[5], funct3, funct7b5, ALUOp, ALUControl);

    assign PCWrite = (Zero & Branch) | PCUpdate;

endmodule 


// КА для контроллера (2)
module main_state_machine(input  logic       clk,
                          input  logic       reset,
                          input  logic [6:0] op,
								  output logic       PCUpdate, 
								  output logic       Branch,
                          output logic       RegWrite, MemWrite,
								  output logic       IRWrite,
                          output logic [1:0] ALUSrcA, ALUSrcB,
								  output logic [1:0] ResultSrc, 
                          output logic       AdrSrc,
								  output logic [1:0] ALUOp);

	typedef enum logic[3:0] {FETCH, 		//S0
                            DECODE, 	//S1
                            MEM_ADR, 	//S2
                            MEM_READ,  //S3
                            MEM_WB,		//S4
                            MEM_WRITE, //S5
                            EXECUTE_R, //S6
                            ALU_WB, 	//S7
                            EXECUTE_I, //S8
                            JAL, 		//S9
                            BEQ 			//S10
                            } statetype;

   statetype state, nextstate;

    // регистр состояния
	always @(posedge clk, posedge reset)
		begin
			if (reset) state <= FETCH;
			else       state <= nextstate;
		end

    // логика след состояния
    always_comb
		case (state)
            FETCH:      nextstate = DECODE;
            DECODE:  if (op == 7'b0000011 || op == 7'b0100011) nextstate = MEM_ADR;
                     else if (op == 7'b0110011)       			nextstate = EXECUTE_R;
                     else if (op == 7'b0010011)   					nextstate = EXECUTE_I;
                     else if (op == 7'b1101111)          		nextstate = JAL;
                     else if (op == 7'b1100011)          		nextstate = BEQ;
                     else                            				nextstate = DECODE;
            MEM_ADR: if (op == 7'b0000011)               		nextstate = MEM_READ;
                     else if (op == 7'b0100011)          		nextstate = MEM_WRITE;
                     else                            				nextstate = MEM_ADR;
            MEM_READ:    nextstate = MEM_WB;
            MEM_WB:      nextstate = FETCH;
            MEM_WRITE:   nextstate = FETCH;
            EXECUTE_R:   nextstate = ALU_WB;
            ALU_WB:      nextstate = FETCH;
            EXECUTE_I:   nextstate = ALU_WB;
            JAL:         nextstate = ALU_WB;
            BEQ:         nextstate = FETCH;
            default:     nextstate = FETCH;
        endcase 
		
    // выходная логика
    assign PCUpdate     = (state == FETCH || state == JAL);
    assign Branch       = (state == BEQ);
    assign RegWrite     = (state == MEM_WB || state == ALU_WB);
    assign MemWrite     = (state == MEM_WRITE);
	 assign IRWrite      = (state == FETCH);
    assign ALUSrcA[0]   = (state == JAL || state == DECODE);
    assign ALUSrcA[1]   = (state == MEM_ADR || state == EXECUTE_R || state == EXECUTE_I || state == BEQ);
    assign ALUSrcB[0]   = (state == MEM_ADR || state == EXECUTE_I || state == DECODE);
    assign ALUSrcB[1]   = (state == JAL || state == FETCH);
	 assign ResultSrc[0] = (state == MEM_WB);
    assign ResultSrc[1] = (state == FETCH);
    assign AdrSrc       = (state == MEM_READ || state == MEM_WRITE);
	 assign ALUOp[0]     = (state == BEQ);
    assign ALUOp[1]     = (state == EXECUTE_R || state == EXECUTE_I);

endmodule 

module instrdec(input  logic [6:0]  op, 
                output logic [1:0] ImmSrc);

    always_comb
        case(op)
				7'b0110011: ImmSrc = 2'bxx; // R-type
				7'b0010011: ImmSrc = 2'b00; // I-type ALU
				7'b0000011: ImmSrc = 2'b00; // lw
				7'b0100011: ImmSrc = 2'b01; // sw
				7'b1100011: ImmSrc = 2'b10; // beq
				7'b1101111: ImmSrc = 2'b11; // jal
				default:    ImmSrc = 2'bxx; // ???
        endcase

endmodule 


// декодер алу (2)
module aludec(input  logic       opb5,
              input  logic [2:0] funct3,
              input  logic       funct7b5, 
              input  logic [1:0] ALUOp,
              output logic [2:0] ALUControl);

    logic  RtypeSub;
    assign RtypeSub = funct7b5 & opb5;  // TRUE for R-type subtract instruction

    always_comb
        case(ALUOp)
            2'b00:                ALUControl = 3'b000; // addition
            2'b01:                ALUControl = 3'b001; // subtraction
            default: case(funct3) // R-type or I-type ALU
                        3'b000: if (RtypeSub) 
                                    ALUControl = 3'b001; // sub
                                else          
                                    ALUControl = 3'b000; // add, addi
                        3'b010:     ALUControl = 3'b101; // slt, slti
                        3'b110:     ALUControl = 3'b011; // or, ori
                        3'b111:     ALUControl = 3'b010; // and, andi
								3'b101:     ALUControl = 3'b111; // srl
                        default:    ALUControl = 3'bxxx; // ???
                     endcase
        endcase
endmodule 


// тракт данных
module datapath(input logic clk, reset,
					 input logic PCWrite, AdrSrc,
                output logic [31:0] Adr,
                input logic IRWrite,
                input logic [31:0] ReadData,
                output logic [31:0] Instr,
                input logic RegWrite,
                input logic [1:0] ImmSrc,
                input logic [1:0] ALUSrcA, ALUSrcB,
                input logic [2:0] ALUControl,
                output logic Zero,
                input logic [1:0] ResultSrc,
                output logic [31:0] WriteData);

    logic [31:0] Result, PC, OLDPC, Data;
    logic [31:0] RD1, RD2, ImmExt, A, B;
    logic [31:0] SrcA, SrcB, ALUResult, ALUOut;

	 // next PC logic
	 flopenr  #(32)  pcFlopenr(clk, reset, PCWrite, Result, PC); 
	 mux2 	 #(32)  pcMux(PC, Result, AdrSrc, Adr);
	 flopenr  #(32)  pcOldFlopenr(clk, reset, IRWrite, PC, OLDPC);	
  	 flopenr  #(32)  pcInstrFlopenr(clk, reset, IRWrite, ReadData, Instr);
	 flopr    #(32)  dataFlopr(clk, reset, ReadData, Data);
 
	 // register file logic
  	 regfile 	 rf(clk, RegWrite, Instr[19:15], Instr[24:20], Instr[11:7], Result, RD1, RD2);
  	 extend 		 ext(Instr[31:7], ImmSrc, ImmExt);
  	 flopr #(32) rd1flopr(clk, reset, RD1, A);
  	 flopr #(32) rd2flopr(clk, reset, RD2, B);

	 assign WriteData = B;

	 // ALU logic
	 mux3  #(32) pcOldMux(PC, OLDPC, A, ALUSrcA, SrcA);
  	 mux3  #(32) immExtMux(B, ImmExt, 4, ALUSrcB, SrcB);
  	 alu 		    a(SrcA, SrcB, ALUControl, ALUResult, Zero);
  	 flopr #(32) resultflopr(clk, reset, ALUResult, ALUOut);
  	 mux3  #(32) resultMux(ALUOut, Data, ALUResult, ResultSrc, Result);

endmodule 


// регистровый файл
module regfile(input  logic        clk, 
               input  logic        we3, 
               input  logic [ 4:0] a1, a2, a3, 
               input  logic [31:0] wd3, 
               output logic [31:0] rd1, rd2);

	logic [31:0] rf[31:0];

	// three ported register file
	// read two ports combinationally (A1/RD1, A2/RD2)
	// write third port on rising edge of clock (A3/WD3/WE3)
	// register 0 hardwired to 0

	always_ff @(posedge clk)
		if (we3) rf[a3] <= wd3;	

	assign rd1 = (a1 != 0) ? rf[a1] : 0;
	assign rd2 = (a2 != 0) ? rf[a2] : 0;
	
endmodule


// сумматор
module adder(input  [31:0] a, b,
             output [31:0] y);

	assign y = a + b;
	
endmodule


// блок расширения знака
module extend(input  logic [31:7] instr,
              input  logic [1:0]  immsrc,
              output logic [31:0] immext);
 
	always_comb
		case(immsrc) 
               // I-type 
			2'b00:   immext = {{20{instr[31]}}, instr[31:20]};  
						// S-type (stores)
			2'b01:   immext = {{20{instr[31]}}, instr[31:25], instr[11:7]}; 
						// B-type (branches)
			2'b10:   immext = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0}; 
						// J-type (jal)
			2'b11:   immext = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0}; 
			default: immext = 32'bx; // undefined
		endcase
		
endmodule


// триггер с сигналом сброса
module flopr #(parameter WIDTH = 8)
              (input  logic             clk, reset,
               input  logic [WIDTH-1:0] d, 
               output logic [WIDTH-1:0] q);

	always_ff @(posedge clk, posedge reset)
		if (reset) q <= 0;
		else       q <= d;
		
endmodule


// триггер с сигналом сброса и выходом выбора
module flopenr #(parameter WIDTH = 8)
                (input  logic             clk, reset, en,
                 input  logic [WIDTH-1:0] d,
                 output logic [WIDTH-1:0] q);

    always_ff @(posedge clk, posedge reset)
        if (reset)   q <= 0;
        else if (en) q <= d;
		  
endmodule 


// мультиплексор 2:1
module mux2 #(parameter WIDTH = 8)
             (input  logic [WIDTH-1:0] d0, d1, 
              input  logic             s, 
              output logic [WIDTH-1:0] y);

	assign y = s ? d1 : d0; 
	
endmodule


// мультиплексор 3:1
module mux3 #(parameter WIDTH = 8)
             (input  logic [WIDTH-1:0] d0, d1, d2,
              input  logic [1:0]       s, 
              output logic [WIDTH-1:0] y);

	assign y = s[1] ? d2 : (s[0] ? d1 : d0); 
	
endmodule


// алушка 
module alu(input  logic [31:0] a, b,
           input  logic [2:0]  alucontrol,
           output logic [31:0] result,
           output logic        zero);

	logic [31:0] condinvb, sum;
	logic        v;              // overflow
	logic        isAddSub;       // true when is add or subtract operation

	assign condinvb = alucontrol[0] ? ~b : b;
	assign sum = a + condinvb + alucontrol[0];
	assign isAddSub = ~alucontrol[2] & ~alucontrol[1] |
					  ~alucontrol[1] & alucontrol[0];

	always_comb
		case (alucontrol)
			3'b000:  result = sum;         // add
			3'b001:  result = sum;         // subtract
			3'b010:  result = a & b;       // and
			3'b011:  result = a | b;       // or
			3'b100:  result = a ^ b;       // xor
			3'b101:  result = sum[31] ^ v; // slt
			3'b110:  result = a << b[4:0]; // sll
			3'b111:  result = a >> b[4:0]; // srl
			default: result = 32'bx;
		endcase

	assign zero = (result == 32'b0);
	assign v = ~(alucontrol[0] ^ a[31] ^ b[31]) & (a[31] ^ sum[31]) & isAddSub;
  
endmodule
