module ysyx_24080014_cpu(
	input clk,
	input rst,
	output reg[31:0]outdata
);

//声明
reg [31:0]next_pc;
//reg wen;//用来判断是否写入
reg [6:0]op;
reg [4:0]rd;
reg [2:0]func3;
reg[31:0]pc;
wire [31:0]ins;
//rs1,imm保存的是地址，需要取出对应的内容，所以需要扩展到32位
reg [31:0] rs1;
reg [31:0] imm;
reg [31:0] rs1_data;
reg [31:0] imm_data;
//初始化
initial begin
	pc = 32'h8000_0000;
	next_pc = pc + 4;
end

//pc
always @(posedge clk or posedge rst)begin
	if(rst)begin
		pc <= 32'h8000_0000;
		next_pc <= pc + 4;		
	end
	else begin
		pc <= next_pc;
		next_pc <= pc + 4;	
	end

end

//IFU取指
ysyx_24080014_ifu ifu(
	.pc(pc),
	.clk(clk),
	.ins(ins)
);

//IDU单纯取指,这里因为是单周期addi指令，所以只有rs1没有rs2
ysyx_24080014_idu idu(
	.ins(ins),
	.op(op),
	.rd(rd),
	.clk(clk),
	.func3(func3),
	.rs1(rs1_data),
	.imm(imm_data)
);

//ALU
ysyx_24080014_alu alu(
	.imm(imm_data),
	.rs1(rs1_data),
	.func3(func3),
	.clk(clk),
	//.wen(wen),
	.outdata(outdata)
);

endmodule
