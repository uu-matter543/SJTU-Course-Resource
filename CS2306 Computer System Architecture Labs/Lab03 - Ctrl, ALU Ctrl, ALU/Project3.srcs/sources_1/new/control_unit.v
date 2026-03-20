`timescale 1ns / 1ps

module control_unit(
    input [5:0] op_code,
    output reg reg_dst,
    output reg alu_src,
    output reg mem_to_reg,
    output reg reg_write,
    output reg mem_read,
    output reg mem_write,
    output reg branch,
    output reg [1:0] alu_op,
    output reg jump
    );

    always @(op_code) begin
        case (op_code)
        6'b000000: begin // R
            reg_dst = 1;
            alu_src = 0;
            mem_to_reg = 0;
            reg_write = 1;
            mem_read = 0;
            mem_write = 0;
            branch = 0;
            alu_op = 2'b10;
            jump = 0;
        end
        6'b100011: begin // lw
            reg_dst = 0;
            alu_src = 1;
            mem_to_reg = 1;
            reg_write = 1;
            mem_read = 1;
            mem_write = 0;
            branch = 0;
            alu_op = 2'b00;
            jump = 0;
        end
        6'b101011: begin // sw
            reg_dst = 0;
            alu_src = 1;
            mem_to_reg = 0;
            reg_write = 0;
            mem_read = 0;
            mem_write = 1;
            branch = 0;
            alu_op = 2'b00;
            jump = 0;
        end
        6'b000100: begin // beq
            reg_dst = 0;
            alu_src = 0;
            mem_to_reg = 0;
            reg_write = 0;
            mem_read = 0;
            mem_write = 0;
            branch = 1;
            alu_op = 2'b01;
            jump = 0;
        end
        6'b000010: begin // J
            reg_dst = 0;
            alu_src = 0;
            mem_to_reg = 0;
            reg_write = 0;
            mem_read = 0;
            mem_write = 0;
            branch = 0;
            alu_op = 2'b00;
            jump = 1;
        end
        default: begin
            reg_dst = 0;
            alu_src = 0;
            mem_to_reg = 0;
            reg_write = 0;
            mem_read = 0;
            mem_write = 0;
            branch = 0;
            alu_op = 2'b00;
            jump = 0;
        end
        endcase
    end

endmodule
