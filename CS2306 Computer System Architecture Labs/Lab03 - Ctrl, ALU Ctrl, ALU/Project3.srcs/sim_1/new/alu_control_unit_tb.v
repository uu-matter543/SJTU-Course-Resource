`timescale 1ns / 1ps

module alu_control_unit_tb(

    );
    reg [5:0] Funct;
    reg [1:0] ALUOp;
    wire [3:0] ALUCtrOut;

    alu_control_unit example_aluctrlu (
        .funct(Funct),
        .alu_op(ALUOp),
        .alu_ctr_out(ALUCtrOut)
    );

    initial begin
        Funct = 0;
        ALUOp = 0;

        #100;
        #100 begin ALUOp = 2'b00; Funct = 8'b000000; end
        #100 begin ALUOp = 2'b01; Funct = 8'b000000; end
        #100 begin ALUOp = 2'b10; Funct = 8'b000000; end
        #100 begin ALUOp = 2'b10; Funct = 8'b000010; end
        #100 begin ALUOp = 2'b10; Funct = 8'b000100; end
        #100 begin ALUOp = 2'b10; Funct = 8'b000101; end
        #100 begin ALUOp = 2'b10; Funct = 8'b001010; end
    end
endmodule
