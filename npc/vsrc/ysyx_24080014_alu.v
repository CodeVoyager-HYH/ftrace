module ysyx_24080014_alu(
	input [31:0]imm,
	input [31:0]rs1,
	input [2:0]func3,
	input clk,
//	output reg wen,
	output reg [31:0]outdata
);
	
	always @(posedge clk)begin
		case(func3) 
			3'b000:begin
				outdata <= 32'b0 + imm;//加法
				//wen <= 1'b1;
				end			
			default:begin
				$display("ERROR!");
		end
		endcase
	end

endmodule
