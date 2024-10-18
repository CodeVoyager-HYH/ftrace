#include <stdint.h>  
#include <string.h>  
#include "verilated_vcd_c.h"  
#include "Vcpu.h"  
#include "verilated.h"  
int main(int argc, char** argv, char** env) {
    if (false && argc && argv) {}
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);

    Vcpu* top = new Vcpu{contextp};

    int i = 0;

    VerilatedVcdC* tfp = new VerilatedVcdC; 
    contextp->traceEverOn(true); 
    top->trace(tfp, 0); 
    tfp->open("wave.vcd"); 

    while (!contextp->gotFinish() && i++ < 20) {
        int imm = rand() & 1;
        int rs1 = rand() & 1;
				
				top->clk = 0;
        top->imm = imm;
        top->rs1 = rs1;
        top->func3 = 000;
        top->eval();
        
        top->clk = 1;
        top->imm = imm;
        top->rs1 = rs1;
        top->func3 = 000;
        top->eval();

        tfp->dump(contextp->time()); 

        contextp->timeInc(1);
    }

    top->final();
    tfp->close(); 

    delete top;

    return 0;
}
