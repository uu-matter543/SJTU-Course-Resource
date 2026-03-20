`timescale 1ns / 1ps

module alu_tb(

    );
    reg [31:0] Operand1;
    reg [31:0] Operand2;
    reg [3:0] AluCtr;
    wire Zero;
    wire [31:0] AluResult;
    
    alu example_alu(
        .reg_1(Operand1),
        .reg_2(Operand2),
        .alu_ctr(AluCtr),
        .zero(Zero),
        .alu_result(AluResult)
        );
    initial begin
        Operand1 = 0;
        Operand2 = 0;
        AluCtr = 0;
        #100 begin Operand1 = 15; Operand2 = 10; AluCtr = 4'b0000; end
        #100 AluCtr = 4'b0001;
        #100 AluCtr = 4'b0010;
        #100 AluCtr = 4'b0110;
        #100 begin Operand1 = 10; Operand2 = 15; end
        #100 begin AluCtr = 4'b0111; Operand1 = 15; Operand2 = 10; end
        #100 begin Operand1 = 10; Operand2 = 15; end
        #100 begin AluCtr = 4'b1100; Operand1 = 1; Operand2 = 1; end
        #100 Operand1 = 16;
    end
endmodule
