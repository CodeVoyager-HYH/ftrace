// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24080014_cpu.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vysyx_24080014_cpu__Syms.h"
#include "Vysyx_24080014_cpu___024root.h"

void Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit(IData/*31:0*/ idx, IData/*31:0*/ &gpr__Vfuncrtn);

VL_ATTR_COLD void Vysyx_24080014_cpu___024root___eval_initial__TOP(Vysyx_24080014_cpu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root___eval_initial__TOP\n"); );
    // Init
    IData/*31:0*/ __Vfunc_gpr__0__Vfuncout;
    __Vfunc_gpr__0__Vfuncout = 0;
    // Body
    Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit(0U, __Vfunc_gpr__0__Vfuncout);
    vlSelf->ysyx_24080014_cpu__DOT__rs1 = __Vfunc_gpr__0__Vfuncout;
    vlSelf->ysyx_24080014_cpu__DOT__pc = 0x80000000U;
    vlSelf->ysyx_24080014_cpu__DOT__next_pc = 0x80000004U;
}
