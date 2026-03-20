`timescale 1ns / 1ps

module control_unit_tb(

    );
    
    reg [5:0] OpCode;
    wire RegDst;
    wire ALUSrc;
    wire MemToReg;
    wire RegWrite;
    wire MemRead;
    wire MemWrite;
    wire Branch;
    wire [1:0] ALUOp;
    wire Jump;
    
    control_unit example_ctrlu (
        .op_code(OpCode),
        .reg_dst(RegDst),
        .alu_src(ALUSrc),
        .mem_to_reg(MemToReg),
        .reg_write(RegWrite),
        .mem_read(MemRead),
        .mem_write(MemWrite),
        .branch(Branch),
        .alu_op(ALUOp),
        .jump(Jump)
        );
    
    initial begin
        OpCode = 0;
        #100;
        #100 OpCode = 6'b000000; // R type
        #100 OpCode = 6'b100011; // lw
        #100 OpCode = 6'b101011; // sw
        #100 OpCode = 6'b000100; // beq
        #100 OpCode = 6'b000010; // J type
        #100 OpCode = 6'b111111; // default
    end
    
endmodule
