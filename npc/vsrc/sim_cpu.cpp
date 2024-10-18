#include <stdint.h>  
#include <string.h>  
#include "verilated_vcd_c.h"  
#include "Vysyx_24080014_cpu.h"  
#include "verilated.h"  
  
// DPI-C 函数  
extern "C" {  
    int gpr(int idx) {  
        return 0; // 假设 0 号寄存器保存的就是 0  
    }  
  
    // 注意：init_mem 在这里可能不需要，因为它没有在主模块中使用  
    // int init_mem(int size) { return 0; }  
}  
  
int main(int argc, char** argv, char** env) {
    if (false && argc && argv) {}
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);

    Vysyx_24080014_cpu* top = new Vysyx_24080014_cpu{contextp};

    int i = 0;

    VerilatedVcdC* tfp = new VerilatedVcdC; 
    contextp->traceEverOn(true); 
    top->trace(tfp, 0); 
    tfp->open("wave.vcd"); 

    while (!contextp->gotFinish() && i++ < 20) {
				
				top->clk = 0;
				top->rst = 0;
        top->eval();
        
        top->clk = 1;
        top->rst = 1;
        top->eval();
        
        top->clk = 0;
        top->rst = 1;
        top->eval();
        
        top->clk = 1;
        top->rst = 0;
        top->eval();

        tfp->dump(contextp->time()); 

        contextp->timeInc(1);
    }

    top->final();
    tfp->close(); 

    delete top;

    return 0;
}

