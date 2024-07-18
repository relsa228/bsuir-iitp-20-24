typedef enum logic[6:0] {r_type_op=7'b0110011, i_type_alu_op=7'b0010011, lw_op=7'b0000011, sw_op=7'b0100011, beq_op=7'b1100011, jal_op=7'b1101111} opcodetype;

module lab04_02(input  logic       clk,
                  input  logic       reset,  
                  input  opcodetype  op,
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


// КА для контроллера
module main_state_machine(input  logic       clk,
                          input  logic       reset,
                          input  opcodetype  op,
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
            DECODE:  if (op == lw_op || op == sw_op) nextstate = MEM_ADR;
                     else if (op == r_type_op)       nextstate = EXECUTE_R;
                     else if (op == i_type_alu_op)   nextstate = EXECUTE_I;
                     else if (op == jal_op)          nextstate = JAL;
                     else if (op == beq_op)          nextstate = BEQ;
                     else                            nextstate = DECODE;
            MEM_ADR: if (op == lw_op)                nextstate = MEM_READ;
                     else if (op == sw_op)           nextstate = MEM_WRITE;
                     else                            nextstate = MEM_ADR;
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
                        default:    ALUControl = 3'bxxx; // ???
                     endcase
        endcase
endmodule 


module instrdec(input  opcodetype  op, 
                 output logic [1:0] ImmSrc);

    always_comb
        case(op)
            r_type_op:     ImmSrc = 2'bxx; // R-type
            i_type_alu_op: ImmSrc = 2'b00; // I-type ALU
            lw_op:         ImmSrc = 2'b00; // lw
            sw_op:         ImmSrc = 2'b01; // sw
            beq_op:        ImmSrc = 2'b10; // beq
            jal_op:        ImmSrc = 2'b11; // jal
            default:       ImmSrc = 2'bxx; // ???
        endcase

endmodule 


module testbench();

    logic        clk;
    logic        reset;
    
    opcodetype  op;
    logic [2:0] funct3;
    logic       funct7b5;
    logic       Zero;
    logic [1:0] ImmSrc;
    logic [1:0] ALUSrcA, ALUSrcB;
    logic [1:0] ResultSrc;
    logic       AdrSrc;
    logic [2:0] ALUControl;
    logic       IRWrite, PCWrite;
    logic       RegWrite, MEM_WRITE;
    
    logic [31:0] vectornum, errors;
    logic [39:0] testvectors[10000:0];
    
    logic        new_error;
    logic [15:0] expected;
    logic [6:0]  hash;


    // instantiate device to be tested
    lab04_02 dut(clk, reset, op, funct3, funct7b5, Zero,
                    ImmSrc, ALUSrcA, ALUSrcB, ResultSrc, AdrSrc, ALUControl, IRWrite, PCWrite, RegWrite, MEM_WRITE);
    
    // generate clock
    always 
        begin
            clk = 1; #5; clk = 0; #5;
        end

    // at start of test, load vectors and pulse reset
    initial
        begin
            $readmemb("controller.tv", testvectors);
            vectornum = 0; errors = 0; hash = 0;
            reset = 1; #22; reset = 0;
        end
        
    // apply test vectors on rising edge of clk
    always @(posedge clk)
        begin
            #1; {op, funct3, funct7b5, Zero, expected} = testvectors[vectornum];
        end

    // check results on falling edge of clk
    always @(negedge clk)
        if (~reset) begin // skip cycles during reset
            new_error=0; 

            if ((ImmSrc!==expected[15:14])&&(expected[15:14]!==2'bxx))  begin
                $display("   ImmSrc = %b      Expected %b", ImmSrc,     expected[15:14]);
                new_error=1;
            end
            if ((ALUSrcA!==expected[13:12])&&(expected[13:12]!==2'bxx)) begin
                $display("   ALUSrcA = %b     Expected %b", ALUSrcA,    expected[13:12]);
                new_error=1;
            end
            if ((ALUSrcB!==expected[11:10])&&(expected[11:10]!==2'bxx)) begin
                $display("   ALUSrcB = %b     Expected %b", ALUSrcB,    expected[11:10]);
                new_error=1;
            end
            if ((ResultSrc!==expected[9:8])&&(expected[9:8]!==2'bxx))   begin
                $display("   ResultSrc = %b   Expected %b", ResultSrc,  expected[9:8]);
                new_error=1;
            end
            if ((AdrSrc!==expected[7])&&(expected[7]!==1'bx))           begin
                $display("   AdrSrc = %b       Expected %b", AdrSrc,     expected[7]);
                new_error=1;
            end
            if ((ALUControl!==expected[6:4])&&(expected[6:4]!==3'bxxx)) begin
                $display("   ALUControl = %b Expected %b", ALUControl, expected[6:4]);
                new_error=1;
            end
            if ((IRWrite!==expected[3])&&(expected[3]!==1'bx))          begin
                $display("   IRWrite = %b      Expected %b", IRWrite,    expected[3]);
                new_error=1;
            end
            if ((PCWrite!==expected[2])&&(expected[2]!==1'bx))          begin
                $display("   PCWrite = %b      Expected %b", PCWrite,    expected[2]);
                new_error=1;
            end
            if ((RegWrite!==expected[1])&&(expected[1]!==1'bx))         begin
                $display("   RegWrite = %b     Expected %b", RegWrite,   expected[1]);
                new_error=1;
            end
            if ((MEM_WRITE!==expected[0])&&(expected[0]!==1'bx))         begin
                $display("   MEM_WRITE = %b     Expected %b", MEM_WRITE,   expected[0]);
                new_error=1;
            end

            if (new_error) begin
                $display("Error on vector %d: inputs: op = %h funct3 = %h funct7b5 = %h", vectornum, op, funct3, funct7b5);
                errors = errors + 1;
            end
            vectornum = vectornum + 1;
            hash = hash ^ {ImmSrc&{2{expected[15:14]!==2'bxx}}, ALUSrcA&{2{expected[13:12]!==2'bxx}}} ^ {ALUSrcB&{2{expected[11:10]!==2'bxx}}, ResultSrc&{2{expected[9:8]!==2'bxx}}} ^ {AdrSrc&{expected[7]!==1'bx}, ALUControl&{3{expected[6:4]!==3'bxxx}}} ^ {IRWrite&{expected[3]!==1'bx}, PCWrite&{expected[2]!==1'bx}, RegWrite&{expected[1]!==1'bx}, MEM_WRITE&{expected[0]!==1'bx}};
            hash = {hash[5:0], hash[6] ^ hash[5]};
            if (testvectors[vectornum] === 40'bx) begin 
                $display("%d tests completed with %d errors", vectornum, errors);
                $display("hash = %h", hash);
                $stop;
            end
        end
endmodule 
