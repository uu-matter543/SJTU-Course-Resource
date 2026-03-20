`timescale 1ns / 1ps

module alu_control_unit(
    input [5:0] funct,
    input [1:0] alu_op,
    output reg [3:0] alu_ctr_out
    );
    
    always @(alu_op or funct) begin
        casex ({alu_op, funct})
        8'b00xxxxxx: alu_ctr_out = 4'b0010;
        8'b01xxxxxx: alu_ctr_out = 4'b0110;
        8'b1xxx0000: alu_ctr_out = 4'b0010;
        8'b1xxx0010: alu_ctr_out = 4'b0110;
        8'b1xxx0100: alu_ctr_out = 4'b0000;
        8'b1xxx0101: alu_ctr_out = 4'b0001;
        8'b1xxx1010: alu_ctr_out = 4'b0111;
        default: alu_ctr_out = 4'b0;
        endcase
    end
endmodule
