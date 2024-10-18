// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24080014_cpu.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vysyx_24080014_cpu__Syms.h"
#include "Vysyx_24080014_cpu___024unit.h"

extern "C" int gpr(int idx);

VL_INLINE_OPT void Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit(IData/*31:0*/ idx, IData/*31:0*/ &gpr__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_24080014_cpu___024unit____Vdpiimwrap_gpr_TOP____024unit\n"); );
    // Body
    int idx__Vcvt;
    for (size_t idx__Vidx = 0; idx__Vidx < 1; ++idx__Vidx) idx__Vcvt = idx;
    int gpr__Vfuncrtn__Vcvt;
    gpr__Vfuncrtn__Vcvt = gpr(idx__Vcvt);
    gpr__Vfuncrtn = gpr__Vfuncrtn__Vcvt;
}
