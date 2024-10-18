// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_24080014_cpu.h for the primary calling header

#ifndef VERILATED_VYSYX_24080014_CPU___024ROOT_H_
#define VERILATED_VYSYX_24080014_CPU___024ROOT_H_  // guard

#include "verilated.h"

class Vysyx_24080014_cpu__Syms;
class Vysyx_24080014_cpu___024unit;


class Vysyx_24080014_cpu___024root final : public VerilatedModule {
  public:
    // CELLS
    Vysyx_24080014_cpu___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*6:0*/ ysyx_24080014_cpu__DOT__op;
    CData/*4:0*/ ysyx_24080014_cpu__DOT__rd;
    CData/*2:0*/ ysyx_24080014_cpu__DOT__func3;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __Vtrigrprev__TOP__rst;
    CData/*0:0*/ __VactContinue;
    VL_OUT(outdata,31,0);
    IData/*31:0*/ ysyx_24080014_cpu__DOT__next_pc;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__pc;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__ins;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__rs1;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__imm;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__rs1_data;
    IData/*31:0*/ ysyx_24080014_cpu__DOT__imm_data;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vysyx_24080014_cpu__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vysyx_24080014_cpu___024root(Vysyx_24080014_cpu__Syms* symsp, const char* v__name);
    ~Vysyx_24080014_cpu___024root();
    VL_UNCOPYABLE(Vysyx_24080014_cpu___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
