// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline_AGEX_STAGE.h"

VL_ATTR_COLD void Vpipeline_AGEX_STAGE___ctor_var_reset(Vpipeline_AGEX_STAGE* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpipeline_AGEX_STAGE___ctor_var_reset\n"); );
    // Body
    vlSelf->__PVT__clk = VL_RAND_RESET_I(1);
    vlSelf->__PVT__reset = VL_RAND_RESET_I(1);
    vlSelf->__PVT__from_MEM_to_AGEX = VL_RAND_RESET_I(1);
    vlSelf->__PVT__from_WB_to_AGEX = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(281, vlSelf->__PVT__from_DE_latch);
    VL_RAND_RESET_W(175, vlSelf->__PVT__AGEX_latch_out);
    VL_RAND_RESET_W(75, vlSelf->__PVT__from_AGEX_to_FE);
    vlSelf->__PVT__from_AGEX_to_DE = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(175, vlSelf->__PVT__AGEX_latch);
    vlSelf->__PVT__aluout_AGEX = VL_RAND_RESET_I(32);
    vlSelf->__PVT__memaddr_AGEX = VL_RAND_RESET_I(32);
    vlSelf->__PVT__br_target_AGEX = VL_RAND_RESET_I(32);
    vlSelf->__PVT__update_btb_pht_AGEX = VL_RAND_RESET_I(1);
    vlSelf->bp_correct_AGEX_reg = VL_RAND_RESET_I(32);
    vlSelf->bp_total_AGEX_reg = VL_RAND_RESET_I(32);
    vlSelf->__VdfgExtracted_hd1356386__0 = VL_RAND_RESET_I(1);
    vlSelf->__VdfgExtracted_h7b65b0e5__0 = VL_RAND_RESET_I(1);
    vlSelf->__VdfgTmp_h296e3b88__0 = 0;
}
