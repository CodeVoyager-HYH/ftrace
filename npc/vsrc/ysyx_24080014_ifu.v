module ysyx_24080014_ifu(
	input [31:0]pc,
	input clk,
	output reg[31:0]ins
);

	//import "DPI-C" function int init_mem(int size);

always @(posedge clk)
 ins = 32'b000000000101_00000000000010010011;


endmodule
