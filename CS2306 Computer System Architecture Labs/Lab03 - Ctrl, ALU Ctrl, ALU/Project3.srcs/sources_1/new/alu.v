`timescale 1ns / 1ps

module alu(
    input [31:0] reg_1,
    input [31:0] reg_2,
    input [3:0] alu_ctr,
    output reg zero,
    output reg [31:0] alu_result
    );
    
    always @(reg_1 or reg_2 or alu_ctr) begin
        case (alu_ctr)
            4'b0000: alu_result = reg_1 & reg_2;
            4'b0001: alu_result = reg_1 | reg_2;
            4'b0010: alu_result = reg_1 + reg_2;
            4'b0110: alu_result = reg_1 - reg_2;
            4'b0111: alu_result = $signed(reg_1) < $signed(reg_2) ? 1 : 0;
            4'b1100: alu_result = ~(reg_1 | reg_2);
        endcase
        if (alu_result == 0) zero = 1;
        else zero = 0;
    end
endmodule
