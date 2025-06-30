`timescale 1ns / 1ps

module flowing_light_tb();
    
reg clock_p;
reg clock_n;
reg reset;
wire [7:0] led;

flowing_light example_flowing_light(
    .clock_p(clock_p),
    .clock_n(clock_n),
    .reset(reset),
    .led(led)
);

parameter PERIOD = 10;
always #(PERIOD*2) clock_p = !clock_p;
always #(PERIOD*2) clock_n = !clock_n;
initial begin
    clock_p = 1'b0;
    clock_n = 1'b1;
    reset = 1'b1;
    # (PERIOD*2) reset = 1'b0;
    # (PERIOD*4) reset = 1'b1;
end

endmodule
