// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24080014_cpu.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vysyx_24080014_cpu__Syms.h"
#include "Vysyx_24080014_cpu___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24080014_cpu___024root___dump_triggers__act(Vysyx_24080014_cpu___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_24080014_cpu___024root___eval_triggers__act(Vysyx_24080014_cpu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.at(0U) = (((IData)(vlSelf->clk) 
                                       & (~ (IData)(vlSelf->__Vtrigrprev__TOP__clk))) 
                                      | ((IData)(vlSelf->rst) 
                                         & (~ (IData)(vlSelf->__Vtrigrprev__TOP__rst))));
    vlSelf->__VactTriggered.at(1U) = ((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigrprev__TOP__clk)));
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
    vlSelf->__Vtrigrprev__TOP__rst = vlSelf->rst;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_24080014_cpu___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit(IData/*31:0*/ idx, IData/*31:0*/ &gpr__Vfuncrtn);

VL_INLINE_OPT void Vysyx_24080014_cpu___024root___nba_sequent__TOP__1(Vysyx_24080014_cpu___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_24080014_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24080014_cpu___024root___nba_sequent__TOP__1\n"); );
    // Init
    IData/*31:0*/ __Vfunc_gpr__0__Vfuncout;
    __Vfunc_gpr__0__Vfuncout = 0;
    // Body
    vlSelf->ysyx_24080014_cpu__DOT__ins = 0x500093U;
    vlSelf->ysyx_24080014_cpu__DOT__imm_data = 5U;
    Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit(0U, __Vfunc_gpr__0__Vfuncout);
    vlSelf->ysyx_24080014_cpu__DOT__rs1_data = __Vfunc_gpr__0__Vfuncout;
    if (VL_LIKELY((0U == (IData)(vlSelf->ysyx_24080014_cpu__DOT__func3)))) {
        vlSelf->outdata = vlSelf->ysyx_24080014_cpu__DOT__imm_data;
    } else {
        VL_WRITEF("ERROR!\n");
    }
}
