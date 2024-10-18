import "DPI-C" function int gpr(int idx);
module ysyx_24080014_idu(//单纯取指
    input [31:0] ins,  // 指令
    output [6:0] op,
    output [4:0] rd,
    input clk,
    output [2:0] func3,
    output reg[31:0] rs1,
    output reg[31:0] imm
);
reg [31:0]ins1;
initial
	ins1 = {{27{1'b0}},ins[19:15]};
always @(posedge clk) begin
    rs1 = gpr(ins1);
    imm = {{20{1'b0}},ins[31:20]};
end
endmodule
