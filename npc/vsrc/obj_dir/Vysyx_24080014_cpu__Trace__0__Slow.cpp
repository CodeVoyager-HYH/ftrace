// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vysyx_24080014_cpu__Syms.h"


VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_init_sub__TOP__0(Vysyx_24080014_cpu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+6,"rst", false,-1);
    tracep->declBus(c+7,"outdata", false,-1, 31,0);
    tracep->pushNamePrefix("ysyx_24080014_cpu ");
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBit(c+6,"rst", false,-1);
    tracep->declBus(c+7,"outdata", false,-1, 31,0);
    tracep->declBus(c+8,"next_pc", false,-1, 31,0);
    tracep->declBus(c+10,"op", false,-1, 6,0);
    tracep->declBus(c+11,"rd", false,-1, 4,0);
    tracep->declBus(c+12,"func3", false,-1, 2,0);
    tracep->declBus(c+9,"pc", false,-1, 31,0);
    tracep->declBus(c+1,"ins", false,-1, 31,0);
    tracep->declBus(c+13,"rs1", false,-1, 31,0);
    tracep->declBus(c+14,"imm", false,-1, 31,0);
    tracep->declBus(c+2,"rs1_data", false,-1, 31,0);
    tracep->declBus(c+3,"imm_data", false,-1, 31,0);
    tracep->pushNamePrefix("alu ");
    tracep->declBus(c+3,"imm", false,-1, 31,0);
    tracep->declBus(c+2,"rs1", false,-1, 31,0);
    tracep->declBus(c+12,"func3", false,-1, 2,0);
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBus(c+7,"outdata", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("idu ");
    tracep->declBus(c+1,"ins", false,-1, 31,0);
    tracep->declBus(c+10,"op", false,-1, 6,0);
    tracep->declBus(c+11,"rd", false,-1, 4,0);
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBus(c+12,"func3", false,-1, 2,0);
    tracep->declBus(c+2,"rs1", false,-1, 31,0);
    tracep->declBus(c+3,"imm", false,-1, 31,0);
    tracep->declBus(c+4,"ins1", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("ifu ");
    tracep->declBus(c+9,"pc", false,-1, 31,0);
    tracep->declBit(c+5,"clk", false,-1);
    tracep->declBus(c+1,"ins", false,-1, 31,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_init_top(Vysyx_24080014_cpu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root__trace_init_top\n"); );
    // Body
    Vysyx_24080014_cpu___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vysyx_24080014_cpu___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vysyx_24080014_cpu___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_register(Vysyx_24080014_cpu___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vysyx_24080014_cpu___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vysyx_24080014_cpu___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vysyx_24080014_cpu___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_full_sub_0(Vysyx_24080014_cpu___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root__trace_full_top_0\n"); );
    // Init
    Vysyx_24080014_cpu___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_24080014_cpu___024root*>(voidSelf);
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vysyx_24080014_cpu___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vysyx_24080014_cpu___024root__trace_full_sub_0(Vysyx_24080014_cpu___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->ysyx_24080014_cpu__DOT__ins),32);
    bufp->fullIData(oldp+2,(vlSelf->ysyx_24080014_cpu__DOT__rs1_data),32);
    bufp->fullIData(oldp+3,(vlSelf->ysyx_24080014_cpu__DOT__imm_data),32);
    bufp->fullIData(oldp+4,((0x1fU & (vlSelf->ysyx_24080014_cpu__DOT__ins 
                                      >> 0xfU))),32);
    bufp->fullBit(oldp+5,(vlSelf->clk));
    bufp->fullBit(oldp+6,(vlSelf->rst));
    bufp->fullIData(oldp+7,(vlSelf->outdata),32);
    bufp->fullIData(oldp+8,(vlSelf->ysyx_24080014_cpu__DOT__next_pc),32);
    bufp->fullIData(oldp+9,(vlSelf->ysyx_24080014_cpu__DOT__pc),32);
    bufp->fullCData(oldp+10,(vlSelf->ysyx_24080014_cpu__DOT__op),7);
    bufp->fullCData(oldp+11,(vlSelf->ysyx_24080014_cpu__DOT__rd),5);
    bufp->fullCData(oldp+12,(vlSelf->ysyx_24080014_cpu__DOT__func3),3);
    bufp->fullIData(oldp+13,(vlSelf->ysyx_24080014_cpu__DOT__rs1),32);
    bufp->fullIData(oldp+14,(vlSelf->ysyx_24080014_cpu__DOT__imm),32);
}
