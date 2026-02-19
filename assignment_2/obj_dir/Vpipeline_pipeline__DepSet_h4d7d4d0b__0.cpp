// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline__Syms.h"
#include "Vpipeline_pipeline.h"

VL_INLINE_OPT void Vpipeline_pipeline___nba_sequent__TOP__pipeline__0(Vpipeline_pipeline* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpipeline_pipeline___nba_sequent__TOP__pipeline__0\n"); );
    // Init
    CData/*7:0*/ __Vdly__my_FE_stage__DOT__BHR;
    __Vdly__my_FE_stage__DOT__BHR = 0;
    CData/*3:0*/ __Vdlyvdim0__my_FE_stage__DOT__tag_BTB__v0;
    __Vdlyvdim0__my_FE_stage__DOT__tag_BTB__v0 = 0;
    IData/*25:0*/ __Vdlyvval__my_FE_stage__DOT__tag_BTB__v0;
    __Vdlyvval__my_FE_stage__DOT__tag_BTB__v0 = 0;
    CData/*0:0*/ __Vdlyvset__my_FE_stage__DOT__tag_BTB__v0;
    __Vdlyvset__my_FE_stage__DOT__tag_BTB__v0 = 0;
    CData/*7:0*/ __Vdlyvdim0__my_FE_stage__DOT__PHT__v0;
    __Vdlyvdim0__my_FE_stage__DOT__PHT__v0 = 0;
    CData/*1:0*/ __Vdlyvval__my_FE_stage__DOT__PHT__v0;
    __Vdlyvval__my_FE_stage__DOT__PHT__v0 = 0;
    CData/*0:0*/ __Vdlyvset__my_FE_stage__DOT__PHT__v0;
    __Vdlyvset__my_FE_stage__DOT__PHT__v0 = 0;
    CData/*7:0*/ __Vdlyvdim0__my_FE_stage__DOT__PHT__v1;
    __Vdlyvdim0__my_FE_stage__DOT__PHT__v1 = 0;
    CData/*1:0*/ __Vdlyvval__my_FE_stage__DOT__PHT__v1;
    __Vdlyvval__my_FE_stage__DOT__PHT__v1 = 0;
    CData/*0:0*/ __Vdlyvset__my_FE_stage__DOT__PHT__v1;
    __Vdlyvset__my_FE_stage__DOT__PHT__v1 = 0;
    CData/*3:0*/ __Vdlyvdim0__my_FE_stage__DOT__target_BTB__v0;
    __Vdlyvdim0__my_FE_stage__DOT__target_BTB__v0 = 0;
    IData/*31:0*/ __Vdlyvval__my_FE_stage__DOT__target_BTB__v0;
    __Vdlyvval__my_FE_stage__DOT__target_BTB__v0 = 0;
    CData/*0:0*/ __Vdlyvset__my_FE_stage__DOT__target_BTB__v0;
    __Vdlyvset__my_FE_stage__DOT__target_BTB__v0 = 0;
    CData/*3:0*/ __Vdlyvdim0__my_FE_stage__DOT__valid_BTB__v0;
    __Vdlyvdim0__my_FE_stage__DOT__valid_BTB__v0 = 0;
    CData/*0:0*/ __Vdlyvset__my_FE_stage__DOT__valid_BTB__v0;
    __Vdlyvset__my_FE_stage__DOT__valid_BTB__v0 = 0;
    IData/*31:0*/ __Vdly__my_FE_stage__DOT__PC_FE_latch;
    __Vdly__my_FE_stage__DOT__PC_FE_latch = 0;
    IData/*31:0*/ __Vdly__my_FE_stage__DOT__inst_count_FE;
    __Vdly__my_FE_stage__DOT__inst_count_FE = 0;
    // Body
    __Vdly__my_FE_stage__DOT__inst_count_FE = vlSelf->__PVT__my_FE_stage__DOT__inst_count_FE;
    __Vdlyvset__my_FE_stage__DOT__valid_BTB__v0 = 0U;
    __Vdly__my_FE_stage__DOT__BHR = vlSelf->__PVT__my_FE_stage__DOT__BHR;
    __Vdlyvset__my_FE_stage__DOT__target_BTB__v0 = 0U;
    __Vdlyvset__my_FE_stage__DOT__tag_BTB__v0 = 0U;
    __Vdly__my_FE_stage__DOT__PC_FE_latch = vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch;
    __Vdlyvset__my_FE_stage__DOT__PHT__v0 = 0U;
    __Vdlyvset__my_FE_stage__DOT__PHT__v1 = 0U;
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[0U];
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U];
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U];
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U];
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U];
    vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U] 
        = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U];
    vlSelf->__Vdlyvset__my_MEM_stage__DOT__dmem__v0 = 0U;
    if (vlSymsp->TOP.reset) {
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[1U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[2U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[3U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[4U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[5U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[6U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[7U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[8U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[9U] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xaU] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xbU] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xcU] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xdU] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xeU] = 0U;
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[0xfU] = 0U;
        vlSelf->__PVT__cycle_count = 0U;
        __Vdly__my_FE_stage__DOT__inst_count_FE = 1U;
        __Vdly__my_FE_stage__DOT__BHR = 0U;
        __Vdly__my_FE_stage__DOT__PC_FE_latch = 0x200U;
        vlSelf->__PVT__my_FE_stage__DOT__i = 0U;
        while (VL_GTS_III(32, 0x100U, vlSelf->__PVT__my_FE_stage__DOT__i)) {
            vlSelf->__PVT__my_FE_stage__DOT__PHT[(0xffU 
                                                  & vlSelf->__PVT__my_FE_stage__DOT__i)] = 1U;
            vlSelf->__PVT__my_FE_stage__DOT__i = ((IData)(1U) 
                                                  + vlSelf->__PVT__my_FE_stage__DOT__i);
        }
        vlSelf->__PVT__my_FE_stage__DOT__i = 0x10U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U] = 0U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U] = 0U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U] = 0U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U] = 0U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U] = 0U;
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__in_use_regs = 0U;
    } else {
        vlSelf->__PVT__cycle_count = ((IData)(1U) + vlSelf->__PVT__cycle_count);
        if ((1U & (~ (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[2U] 
                      >> 0xaU)))) {
            if ((1U & (~ (IData)(vlSelf->__PVT__from_DE_to_FE)))) {
                __Vdly__my_FE_stage__DOT__inst_count_FE 
                    = ((IData)(1U) + vlSelf->__PVT__my_FE_stage__DOT__inst_count_FE);
            }
        }
        if ((0x200U & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U])) {
            __Vdly__my_FE_stage__DOT__BHR = ((0xfeU 
                                              & ((IData)(vlSelf->__PVT__my_FE_stage__DOT__BHR) 
                                                 << 1U)) 
                                             | (1U 
                                                & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U] 
                                                   >> 8U)));
            if ((0x100U & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U])) {
                if ((3U != vlSelf->__PVT__my_FE_stage__DOT__PHT
                     [(0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U])])) {
                    __Vdlyvval__my_FE_stage__DOT__PHT__v0 
                        = (3U & ((IData)(1U) + vlSelf->__PVT__my_FE_stage__DOT__PHT
                                 [(0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U])]));
                    __Vdlyvset__my_FE_stage__DOT__PHT__v0 = 1U;
                    __Vdlyvdim0__my_FE_stage__DOT__PHT__v0 
                        = (0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U]);
                }
            } else if ((0U != vlSelf->__PVT__my_FE_stage__DOT__PHT
                        [(0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U])])) {
                __Vdlyvval__my_FE_stage__DOT__PHT__v1 
                    = (3U & (vlSelf->__PVT__my_FE_stage__DOT__PHT
                             [(0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U])] 
                             - (IData)(1U)));
                __Vdlyvset__my_FE_stage__DOT__PHT__v1 = 1U;
                __Vdlyvdim0__my_FE_stage__DOT__PHT__v1 
                    = (0xffU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U]);
            }
        }
        if ((0x400U & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[2U])) {
            __Vdly__my_FE_stage__DOT__PC_FE_latch = 
                ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[2U] 
                  << 0x16U) | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U] 
                               >> 0xaU));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U] = 0U;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U] = 0U;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U] = 0U;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U] = 0U;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U] = 0U;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U] = 0U;
        } else if (vlSelf->__PVT__from_DE_to_FE) {
            __Vdly__my_FE_stage__DOT__PC_FE_latch = vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[0U];
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U];
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U];
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U];
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U];
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U] 
                = vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U];
        } else {
            __Vdly__my_FE_stage__DOT__PC_FE_latch = vlSelf->__PVT__my_FE_stage__DOT__pred_next_PC_FE;
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U] 
                = ((vlSelf->__PVT__my_FE_stage__DOT__pred_next_PC_FE 
                    << 8U) | (IData)(vlSelf->__PVT__my_FE_stage__DOT__pht_idx_FE));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U] 
                = ((vlSelf->__PVT__my_FE_stage__DOT__pred_next_PC_FE 
                    >> 0x18U) | (vlSelf->__PVT__my_FE_stage__DOT__inst_count_FE 
                                 << 8U));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U] 
                = ((vlSelf->__PVT__my_FE_stage__DOT__inst_count_FE 
                    >> 0x18U) | (((IData)(4U) + vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch) 
                                 << 8U));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U] 
                = ((((IData)(4U) + vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch) 
                    >> 0x18U) | ((IData)((((QData)((IData)(
                                                           vlSelf->__PVT__my_FE_stage__DOT__imem
                                                           [
                                                           (0x3fffU 
                                                            & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                                               >> 2U))])) 
                                           << 0x20U) 
                                          | (QData)((IData)(vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch)))) 
                                 << 8U));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U] 
                = (((IData)((((QData)((IData)(vlSelf->__PVT__my_FE_stage__DOT__imem
                                              [(0x3fffU 
                                                & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                                   >> 2U))])) 
                              << 0x20U) | (QData)((IData)(vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch)))) 
                    >> 0x18U) | ((IData)(((((QData)((IData)(
                                                            vlSelf->__PVT__my_FE_stage__DOT__imem
                                                            [
                                                            (0x3fffU 
                                                             & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                                                >> 2U))])) 
                                            << 0x20U) 
                                           | (QData)((IData)(vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch))) 
                                          >> 0x20U)) 
                                 << 8U));
            vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U] 
                = (0x100U | ((IData)(((((QData)((IData)(
                                                        vlSelf->__PVT__my_FE_stage__DOT__imem
                                                        [
                                                        (0x3fffU 
                                                         & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                                            >> 2U))])) 
                                        << 0x20U) | (QData)((IData)(vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch))) 
                                      >> 0x20U)) >> 0x18U));
        }
        if (((~ (IData)(vlSelf->__PVT__from_DE_to_FE)) 
             & (IData)(vlSelf->__PVT__my_DE_stage__DOT__wr_reg_DE))) {
            vlSelf->__PVT__my_DE_stage__DOT__in_use_regs 
                = (vlSelf->__PVT__my_DE_stage__DOT__in_use_regs 
                   | (0xffffffffULL & ((IData)(1U) 
                                       << (0x1fU & 
                                           (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                            >> 0xfU)))));
        }
        if ((1U & (IData)((vlSymsp->TOP__pipeline__my_WB_stage.__PVT__from_WB_to_DE 
                           >> 0x25U)))) {
            vlSelf->__PVT__my_DE_stage__DOT__in_use_regs 
                = ((~ ((IData)(1U) << (0x1fU & (IData)(
                                                       (vlSymsp->TOP__pipeline__my_WB_stage.__PVT__from_WB_to_DE 
                                                        >> 0x20U))))) 
                   & vlSelf->__PVT__my_DE_stage__DOT__in_use_regs);
        }
    }
    if ((1U & (~ (IData)(vlSymsp->TOP.reset)))) {
        if ((0x200U & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U])) {
            __Vdlyvset__my_FE_stage__DOT__valid_BTB__v0 = 1U;
            __Vdlyvdim0__my_FE_stage__DOT__valid_BTB__v0 
                = (0xfU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U] 
                           >> 0xaU));
            __Vdlyvval__my_FE_stage__DOT__target_BTB__v0 
                = ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[2U] 
                    << 0x16U) | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U] 
                                 >> 0xaU));
            __Vdlyvset__my_FE_stage__DOT__target_BTB__v0 = 1U;
            __Vdlyvdim0__my_FE_stage__DOT__target_BTB__v0 
                = (0xfU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U] 
                           >> 0xaU));
            __Vdlyvval__my_FE_stage__DOT__tag_BTB__v0 
                = (0x3ffffffU & ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[1U] 
                                  << 0x12U) | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U] 
                                               >> 0xeU)));
            __Vdlyvset__my_FE_stage__DOT__tag_BTB__v0 = 1U;
            __Vdlyvdim0__my_FE_stage__DOT__tag_BTB__v0 
                = (0xfU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_FE[0U] 
                           >> 0xaU));
        }
    }
    if ((0x40U & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U])) {
        vlSelf->__Vdlyvval__my_MEM_stage__DOT__dmem__v0 
            = ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                << 0x18U) | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U] 
                             >> 8U));
        vlSelf->__Vdlyvset__my_MEM_stage__DOT__dmem__v0 = 1U;
        vlSelf->__Vdlyvdim0__my_MEM_stage__DOT__dmem__v0 
            = (0x3fffU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                          >> 0xaU));
    }
    if (__Vdlyvset__my_FE_stage__DOT__valid_BTB__v0) {
        vlSelf->__PVT__my_FE_stage__DOT__valid_BTB[__Vdlyvdim0__my_FE_stage__DOT__valid_BTB__v0] = 1U;
    }
    vlSelf->__PVT__my_FE_stage__DOT__BHR = __Vdly__my_FE_stage__DOT__BHR;
    if (__Vdlyvset__my_FE_stage__DOT__target_BTB__v0) {
        vlSelf->__PVT__my_FE_stage__DOT__target_BTB[__Vdlyvdim0__my_FE_stage__DOT__target_BTB__v0] 
            = __Vdlyvval__my_FE_stage__DOT__target_BTB__v0;
    }
    if (__Vdlyvset__my_FE_stage__DOT__tag_BTB__v0) {
        vlSelf->__PVT__my_FE_stage__DOT__tag_BTB[__Vdlyvdim0__my_FE_stage__DOT__tag_BTB__v0] 
            = __Vdlyvval__my_FE_stage__DOT__tag_BTB__v0;
    }
    if (__Vdlyvset__my_FE_stage__DOT__PHT__v0) {
        vlSelf->__PVT__my_FE_stage__DOT__PHT[__Vdlyvdim0__my_FE_stage__DOT__PHT__v0] 
            = __Vdlyvval__my_FE_stage__DOT__PHT__v0;
    }
    if (__Vdlyvset__my_FE_stage__DOT__PHT__v1) {
        vlSelf->__PVT__my_FE_stage__DOT__PHT[__Vdlyvdim0__my_FE_stage__DOT__PHT__v1] 
            = __Vdlyvval__my_FE_stage__DOT__PHT__v1;
    }
    vlSelf->__PVT__my_FE_stage__DOT__inst_count_FE 
        = __Vdly__my_FE_stage__DOT__inst_count_FE;
    vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch = __Vdly__my_FE_stage__DOT__PC_FE_latch;
    vlSelf->__PVT__my_FE_stage__DOT__pht_idx_FE = (0xffU 
                                                   & ((vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                                       >> 2U) 
                                                      ^ (IData)(vlSelf->__PVT__my_FE_stage__DOT__BHR)));
    vlSelf->__PVT__my_FE_stage__DOT__pred_next_PC_FE 
        = (((vlSelf->__PVT__my_FE_stage__DOT__valid_BTB
             [(0xfU & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                       >> 2U))] & (vlSelf->__PVT__my_FE_stage__DOT__tag_BTB
                                   [(0xfU & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                             >> 2U))] 
                                   == (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                                       >> 6U))) & (
                                                   vlSelf->__PVT__my_FE_stage__DOT__PHT
                                                   [vlSelf->__PVT__my_FE_stage__DOT__pht_idx_FE] 
                                                   >> 1U))
            ? vlSelf->__PVT__my_FE_stage__DOT__target_BTB
           [(0xfU & (vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch 
                     >> 2U))] : ((IData)(4U) + vlSelf->__PVT__my_FE_stage__DOT__PC_FE_latch));
}

VL_INLINE_OPT void Vpipeline_pipeline___nba_sequent__TOP__pipeline__1(Vpipeline_pipeline* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpipeline_pipeline___nba_sequent__TOP__pipeline__1\n"); );
    // Body
    if (vlSymsp->TOP.reset) {
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[0U] = 0U;
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[1U] = 0U;
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[2U] = 0U;
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[3U] = 0U;
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[4U] = 0U;
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[5U] = 0U;
    } else {
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[0U] 
            = (((IData)((((QData)((IData)(vlSelf->__PVT__my_MEM_stage__DOT__dmem
                                          [(0x3fffU 
                                            & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                               >> 0xaU))])) 
                          << 0x20U) | (QData)((IData)(
                                                      ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                        << 0x18U) 
                                                       | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U] 
                                                          >> 8U)))))) 
                << 6U) | (0x3fU & vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U]));
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[1U] 
            = (((IData)((((QData)((IData)(vlSelf->__PVT__my_MEM_stage__DOT__dmem
                                          [(0x3fffU 
                                            & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                               >> 0xaU))])) 
                          << 0x20U) | (QData)((IData)(
                                                      ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                        << 0x18U) 
                                                       | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U] 
                                                          >> 8U)))))) 
                >> 0x1aU) | ((IData)(((((QData)((IData)(
                                                        vlSelf->__PVT__my_MEM_stage__DOT__dmem
                                                        [
                                                        (0x3fffU 
                                                         & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                            >> 0xaU))])) 
                                        << 0x20U) | (QData)((IData)(
                                                                    ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                                      << 0x18U) 
                                                                     | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U] 
                                                                        >> 8U))))) 
                                      >> 0x20U)) << 6U));
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[2U] 
            = (((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[3U] 
                 << 0x1eU) | (0x3fffffc0U & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[2U] 
                                             >> 2U))) 
               | ((IData)(((((QData)((IData)(vlSelf->__PVT__my_MEM_stage__DOT__dmem
                                             [(0x3fffU 
                                               & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                  >> 0xaU))])) 
                             << 0x20U) | (QData)((IData)(
                                                         ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[1U] 
                                                           << 0x18U) 
                                                          | (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[0U] 
                                                             >> 8U))))) 
                           >> 0x20U)) >> 0x1aU));
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[3U] 
            = ((0x3fU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[3U] 
                         >> 2U)) | ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[4U] 
                                     << 0x1eU) | (0x3fffffc0U 
                                                  & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[3U] 
                                                     >> 2U))));
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[4U] 
            = ((0x3fU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[4U] 
                         >> 2U)) | ((vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[5U] 
                                     << 0x1eU) | (0x3fffffc0U 
                                                  & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[4U] 
                                                     >> 2U))));
        vlSelf->__PVT__my_MEM_stage__DOT__MEM_latch[5U] 
            = ((0x3fU & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[5U] 
                         >> 2U)) | (0x1fc0U & (vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__AGEX_latch[5U] 
                                               >> 2U)));
    }
    if (vlSelf->__Vdlyvset__my_MEM_stage__DOT__dmem__v0) {
        vlSelf->__PVT__my_MEM_stage__DOT__dmem[vlSelf->__Vdlyvdim0__my_MEM_stage__DOT__dmem__v0] 
            = vlSelf->__Vdlyvval__my_MEM_stage__DOT__dmem__v0;
    }
}

extern const VlWide<9>/*287:0*/ Vpipeline__ConstPool__CONST_h8ed2b23a_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vpipeline__ConstPool__TABLE_hedfdecc6_0;
extern const VlUnpacked<CData/*0:0*/, 16> Vpipeline__ConstPool__TABLE_hca12deac_0;

VL_INLINE_OPT void Vpipeline_pipeline___nba_sequent__TOP__pipeline__2(Vpipeline_pipeline* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpipeline_pipeline___nba_sequent__TOP__pipeline__2\n"); );
    // Init
    CData/*0:0*/ my_DE_stage__DOT____VdfgTmp_h812efac5__0;
    my_DE_stage__DOT____VdfgTmp_h812efac5__0 = 0;
    CData/*0:0*/ my_DE_stage__DOT____VdfgTmp_h4d9e22c1__0;
    my_DE_stage__DOT____VdfgTmp_h4d9e22c1__0 = 0;
    CData/*0:0*/ my_DE_stage__DOT____VdfgTmp_h897c7e7b__0;
    my_DE_stage__DOT____VdfgTmp_h897c7e7b__0 = 0;
    CData/*0:0*/ my_DE_stage__DOT____VdfgTmp_h3a872c77__0;
    my_DE_stage__DOT____VdfgTmp_h3a872c77__0 = 0;
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<6>/*191:0*/ __Vtemp_6;
    // Body
    __Vtemp_5[0U] = ((1U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE))
                      ? (((- (IData)((1U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                            >> 7U)))) 
                          << 0xbU) | (0x7ffU & ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                                 << 4U) 
                                                | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                   >> 0x1cU))))
                      : ((4U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE))
                          ? (((- (IData)((1U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                                >> 7U)))) 
                              << 0xbU) | ((0x7e0U & 
                                           (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                            << 4U)) 
                                          | (0x1fU 
                                             & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                >> 0xfU))))
                          : ((5U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE))
                              ? (((- (IData)((1U & 
                                              (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                               >> 7U)))) 
                                  << 0xcU) | ((0x800U 
                                               & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                  >> 4U)) 
                                              | ((0x7e0U 
                                                  & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                                     << 4U)) 
                                                 | (0x1eU 
                                                    & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                       >> 0xfU)))))
                              : ((3U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE))
                                  ? (0xfffff000U & 
                                     ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                       << 0x18U) | 
                                      (0xfff000U & 
                                       (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                        >> 8U)))) : 
                                 ((2U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE))
                                   ? (((- (IData)((1U 
                                                   & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                                      >> 7U)))) 
                                       << 0x14U) | 
                                      ((0xff000U & 
                                        (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                         >> 8U)) | 
                                       ((0x800U & (
                                                   vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                   >> 0x11U)) 
                                        | (0x7feU & 
                                           ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                             << 4U) 
                                            | (0xeU 
                                               & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                  >> 0x1cU)))))))
                                   : 0U)))));
    __Vtemp_6[0U] = (IData)((((QData)((IData)(((0x1cU 
                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                               | ((0x1dU 
                                                   == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                  | ((0x1eU 
                                                      == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                     | ((0x1fU 
                                                         == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                        | ((0x20U 
                                                            == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                           | (0x21U 
                                                              == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))))))))) 
                              << 0x31U) | (((QData)((IData)(
                                                            ((0x19U 
                                                              == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                             | ((0x1aU 
                                                                 == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                | (0x1bU 
                                                                   == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))))) 
                                            << 0x30U) 
                                           | (((QData)((IData)(
                                                               (0x17U 
                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) 
                                               << 0x2fU) 
                                              | (((QData)((IData)(
                                                                  (0x18U 
                                                                   == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) 
                                                  << 0x2eU) 
                                                 | (((QData)((IData)(vlSelf->__PVT__my_DE_stage__DOT__wr_reg_DE)) 
                                                     << 0x2dU) 
                                                    | (((QData)((IData)(
                                                                        (0x1fU 
                                                                         & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                            >> 0xfU)))) 
                                                        << 0x28U) 
                                                       | (0xffffffffffULL 
                                                          & (((QData)((IData)(
                                                                              vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U])) 
                                                              << 0x20U) 
                                                             | (QData)((IData)(
                                                                               vlSelf->__PVT__my_FE_stage__DOT__FE_latch[0U])))))))))));
    __Vtemp_6[1U] = ((__Vtemp_5[0U] << 0x12U) | (IData)(
                                                        ((((QData)((IData)(
                                                                           ((0x1cU 
                                                                             == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                            | ((0x1dU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                               | ((0x1eU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x1fU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x20U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | (0x21U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))))))))) 
                                                           << 0x31U) 
                                                          | (((QData)((IData)(
                                                                              ((0x19U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                               | ((0x1aU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | (0x1bU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))))) 
                                                              << 0x30U) 
                                                             | (((QData)((IData)(
                                                                                (0x17U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) 
                                                                 << 0x2fU) 
                                                                | (((QData)((IData)(
                                                                                (0x18U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) 
                                                                    << 0x2eU) 
                                                                   | (((QData)((IData)(vlSelf->__PVT__my_DE_stage__DOT__wr_reg_DE)) 
                                                                       << 0x2dU) 
                                                                      | (((QData)((IData)(
                                                                                (0x1fU 
                                                                                & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                                >> 0xfU)))) 
                                                                          << 0x28U) 
                                                                         | (0xffffffffffULL 
                                                                            & (((QData)((IData)(
                                                                                vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U])) 
                                                                                << 0x20U) 
                                                                               | (QData)((IData)(
                                                                                vlSelf->__PVT__my_FE_stage__DOT__FE_latch[0U])))))))))) 
                                                         >> 0x20U)));
    if (vlSymsp->TOP.reset) {
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[0U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[0U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[1U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[1U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[2U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[2U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[3U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[3U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[4U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[4U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[5U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[5U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[6U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[6U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[7U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[7U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[8U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[8U];
    } else if (vlSelf->__PVT__from_DE_to_FE) {
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[0U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[0U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[1U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[1U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[2U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[2U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[3U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[3U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[4U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[4U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[5U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[5U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[6U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[6U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[7U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[7U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[8U] 
            = Vpipeline__ConstPool__CONST_h8ed2b23a_0[8U];
    } else {
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[0U] 
            = __Vtemp_6[0U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[1U] 
            = __Vtemp_6[1U];
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[2U] 
            = ((__Vtemp_5[0U] >> 0xeU) | (vlSelf->__PVT__my_DE_stage__DOT__regs
                                          [(0x1fU & 
                                            ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                              << 4U) 
                                             | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                >> 0x1cU)))] 
                                          << 0x12U));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[3U] 
            = ((vlSelf->__PVT__my_DE_stage__DOT__regs
                [(0x1fU & ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                            << 4U) | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                      >> 0x1cU)))] 
                >> 0xeU) | ((IData)((((QData)((IData)(
                                                      ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                                                        << 0x18U) 
                                                       | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U] 
                                                          >> 8U)))) 
                                      << 0x20U) | (QData)((IData)(
                                                                  vlSelf->__PVT__my_DE_stage__DOT__regs
                                                                  [
                                                                  (0x1fU 
                                                                   & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                      >> 0x17U))])))) 
                            << 0x12U));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[4U] 
            = (((IData)((((QData)((IData)(((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                                            << 0x18U) 
                                           | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U] 
                                              >> 8U)))) 
                          << 0x20U) | (QData)((IData)(
                                                      vlSelf->__PVT__my_DE_stage__DOT__regs
                                                      [
                                                      (0x1fU 
                                                       & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                          >> 0x17U))])))) 
                >> 0xeU) | ((IData)(((((QData)((IData)(
                                                       ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                                                         << 0x18U) 
                                                        | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U] 
                                                           >> 8U)))) 
                                       << 0x20U) | (QData)((IData)(
                                                                   vlSelf->__PVT__my_DE_stage__DOT__regs
                                                                   [
                                                                   (0x1fU 
                                                                    & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                       >> 0x17U))]))) 
                                     >> 0x20U)) << 0x12U));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[5U] 
            = ((0xff000000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                               << 0x10U)) | (((IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE) 
                                              << 0x12U) 
                                             | ((IData)(
                                                        ((((QData)((IData)(
                                                                           ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                                                                             << 0x18U) 
                                                                            | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U] 
                                                                               >> 8U)))) 
                                                           << 0x20U) 
                                                          | (QData)((IData)(
                                                                            vlSelf->__PVT__my_DE_stage__DOT__regs
                                                                            [
                                                                            (0x1fU 
                                                                             & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                                >> 0x17U))]))) 
                                                         >> 0x20U)) 
                                                >> 0xeU)));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[6U] 
            = (((0xff0000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U] 
                              << 0x10U)) | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] 
                                            >> 0x10U)) 
               | (0xff000000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U] 
                                 << 0x10U)));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[7U] 
            = (((0xff0000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                              << 0x10U)) | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U] 
                                            >> 0x10U)) 
               | (0xff000000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                 << 0x10U)));
        vlSelf->__PVT__my_DE_stage__DOT__DE_latch[8U] 
            = (((0xff0000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                              << 0x10U)) | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                            >> 0x10U)) 
               | (0x1000000U & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                << 0x10U)));
    }
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[0U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[0U];
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[1U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[1U];
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[2U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[2U];
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[3U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[3U];
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[4U];
    vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] = 
        vlSelf->__Vdly__my_FE_stage__DOT__FE_latch[5U];
    my_DE_stage__DOT____VdfgTmp_h812efac5__0 = (IData)(
                                                       (0x3300U 
                                                        == 
                                                        (0x707f00U 
                                                         & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])));
    my_DE_stage__DOT____VdfgTmp_h4d9e22c1__0 = (IData)(
                                                       (0x503300U 
                                                        == 
                                                        (0x707f00U 
                                                         & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])));
    my_DE_stage__DOT____VdfgTmp_h897c7e7b__0 = (IData)(
                                                       ((0x100000U 
                                                         == 
                                                         (0x700000U 
                                                          & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                        & (0U 
                                                           == 
                                                           (0xfeU 
                                                            & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))));
    my_DE_stage__DOT____VdfgTmp_h3a872c77__0 = (IData)(
                                                       (0x501300U 
                                                        == 
                                                        (0x707f00U 
                                                         & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])));
    vlSelf->__PVT__my_DE_stage__DOT__op_I_DE = (((IData)(my_DE_stage__DOT____VdfgTmp_h812efac5__0) 
                                                 & (0U 
                                                    == 
                                                    (0xfeU 
                                                     & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                 ? 1U
                                                 : 
                                                (((IData)(my_DE_stage__DOT____VdfgTmp_h812efac5__0) 
                                                  & (0x40U 
                                                     == 
                                                     (0xfeU 
                                                      & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                  ? 2U
                                                  : 
                                                 ((IData)(
                                                          ((0x703300U 
                                                            == 
                                                            (0x707f00U 
                                                             & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                           & (0U 
                                                              == 
                                                              (0xfeU 
                                                               & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))))
                                                   ? 3U
                                                   : 
                                                  ((IData)(
                                                           ((0x603300U 
                                                             == 
                                                             (0x707f00U 
                                                              & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                            & (0U 
                                                               == 
                                                               (0xfeU 
                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))))
                                                    ? 4U
                                                    : 
                                                   ((IData)(
                                                            ((0x403300U 
                                                              == 
                                                              (0x707f00U 
                                                               & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                             & (0U 
                                                                == 
                                                                (0xfeU 
                                                                 & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))))
                                                     ? 5U
                                                     : 
                                                    ((IData)(
                                                             ((0x203300U 
                                                               == 
                                                               (0x707f00U 
                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                              & (0U 
                                                                 == 
                                                                 (0xfeU 
                                                                  & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))))
                                                      ? 6U
                                                      : 
                                                     ((IData)(
                                                              ((0x303300U 
                                                                == 
                                                                (0x707f00U 
                                                                 & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                               & (0U 
                                                                  == 
                                                                  (0xfeU 
                                                                   & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U]))))
                                                       ? 7U
                                                       : 
                                                      (((IData)(my_DE_stage__DOT____VdfgTmp_h4d9e22c1__0) 
                                                        & (0x40U 
                                                           == 
                                                           (0xfeU 
                                                            & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                        ? 8U
                                                        : 
                                                       (((IData)(my_DE_stage__DOT____VdfgTmp_h4d9e22c1__0) 
                                                         & (0U 
                                                            == 
                                                            (0xfeU 
                                                             & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                         ? 9U
                                                         : 
                                                        ((IData)(
                                                                 ((0x3300U 
                                                                   == 
                                                                   (0x7f00U 
                                                                    & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                                  & (IData)(my_DE_stage__DOT____VdfgTmp_h897c7e7b__0)))
                                                          ? 0xaU
                                                          : 
                                                         (((IData)(my_DE_stage__DOT____VdfgTmp_h812efac5__0) 
                                                           & (2U 
                                                              == 
                                                              (0xfeU 
                                                               & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                           ? 0xbU
                                                           : 
                                                          ((IData)(
                                                                   (0x1300U 
                                                                    == 
                                                                    (0x707f00U 
                                                                     & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                            ? 0xcU
                                                            : 
                                                           ((IData)(
                                                                    (0x701300U 
                                                                     == 
                                                                     (0x707f00U 
                                                                      & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                             ? 0xdU
                                                             : 
                                                            ((IData)(
                                                                     (0x601300U 
                                                                      == 
                                                                      (0x707f00U 
                                                                       & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                              ? 0xeU
                                                              : 
                                                             ((IData)(
                                                                      (0x401300U 
                                                                       == 
                                                                       (0x707f00U 
                                                                        & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                               ? 0xfU
                                                               : 
                                                              ((IData)(
                                                                       (0x201300U 
                                                                        == 
                                                                        (0x707f00U 
                                                                         & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                ? 0x10U
                                                                : 
                                                               ((IData)(
                                                                        (0x301300U 
                                                                         == 
                                                                         (0x707f00U 
                                                                          & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                 ? 0x11U
                                                                 : 
                                                                (((IData)(my_DE_stage__DOT____VdfgTmp_h3a872c77__0) 
                                                                  & (0x40U 
                                                                     == 
                                                                     (0xfeU 
                                                                      & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                                  ? 0x12U
                                                                  : 
                                                                 (((IData)(my_DE_stage__DOT____VdfgTmp_h3a872c77__0) 
                                                                   & (0U 
                                                                      == 
                                                                      (0xfeU 
                                                                       & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U])))
                                                                   ? 0x13U
                                                                   : 
                                                                  ((IData)(
                                                                           ((0x1300U 
                                                                             == 
                                                                             (0x7f00U 
                                                                              & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])) 
                                                                            & (IData)(my_DE_stage__DOT____VdfgTmp_h897c7e7b__0)))
                                                                    ? 0x14U
                                                                    : 
                                                                   ((0x37U 
                                                                     == 
                                                                     (0x7fU 
                                                                      & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                         >> 8U)))
                                                                     ? 0x15U
                                                                     : 
                                                                    ((0x17U 
                                                                      == 
                                                                      (0x7fU 
                                                                       & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                          >> 8U)))
                                                                      ? 0x16U
                                                                      : 
                                                                     ((IData)(
                                                                              (0x200300U 
                                                                               == 
                                                                               (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                       ? 0x17U
                                                                       : 
                                                                      ((IData)(
                                                                               (0x202300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                        ? 0x18U
                                                                        : 
                                                                       ((0x6fU 
                                                                         == 
                                                                         (0x7fU 
                                                                          & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                                             >> 8U)))
                                                                         ? 0x19U
                                                                         : 
                                                                        ((IData)(
                                                                                (0x6700U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                          ? 0x1bU
                                                                          : 
                                                                         ((IData)(
                                                                                (0x6300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                           ? 0x1cU
                                                                           : 
                                                                          ((IData)(
                                                                                (0x106300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                            ? 0x1dU
                                                                            : 
                                                                           ((IData)(
                                                                                (0x406300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                             ? 0x1eU
                                                                             : 
                                                                            ((IData)(
                                                                                (0x506300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                              ? 0x1fU
                                                                              : 
                                                                             ((IData)(
                                                                                (0x606300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                               ? 0x20U
                                                                               : 
                                                                              ((IData)(
                                                                                (0x706300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                                ? 0x21U
                                                                                : 
                                                                               ((IData)(
                                                                                (0x207300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((IData)(
                                                                                (0x107300U 
                                                                                == 
                                                                                (0x707f00U 
                                                                                & vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U])))
                                                                                 ? 0x23U
                                                                                 : 0x25U))))))))))))))))))))))))))))))))));
    vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE 
        = vlSelf->my_DE_stage__DOT____Vxrand_h8d967414__0;
    if ((1U & (~ (((((((((((1U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                           | (2U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                          | (3U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                         | (4U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                        | (5U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                       | (6U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                      | (7U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                     | (8U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                    | (9U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                   | (0xaU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                  | (0xbU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))))) {
        if ((((((((((((0x22U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                      | (0x23U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                     | (0xcU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                    | (0xdU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                   | (0xeU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                  | (0xfU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                 | (0x10U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                | (0x11U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
               | (0x17U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
              | (0x1aU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
             | (0x1bU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 1U;
        } else if ((((0x12U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                     | (0x13U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                    | (0x14U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 1U;
        } else if (((0x15U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                    | (0x16U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 3U;
        } else if ((0x18U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 4U;
        } else if ((0x19U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 2U;
        } else if (((((((0x1cU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                        | (0x1dU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                       | (0x1eU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                      | (0x1fU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                     | (0x20U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                    | (0x21U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
            vlSelf->__PVT__my_DE_stage__DOT__type_immediate_DE = 5U;
        }
    }
    vlSelf->__PVT__my_DE_stage__DOT__wr_reg_DE = ((
                                                   (0x22U 
                                                    == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                   | ((1U 
                                                       == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                      | ((2U 
                                                          == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                         | ((3U 
                                                             == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                            | ((4U 
                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                               | ((5U 
                                                                   == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                  | ((6U 
                                                                      == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                     | ((7U 
                                                                         == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                        | ((8U 
                                                                            == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                           | ((9U 
                                                                               == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                              | ((0xaU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0xbU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0xcU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0xdU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0xeU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0xfU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x10U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x11U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x12U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x13U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x14U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x15U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x16U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x17U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | ((0x19U 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                                                                                | (0x1bU 
                                                                                == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))))))))))))))))))))))))))) 
                                                  & (0U 
                                                     != 
                                                     (0x1fU 
                                                      & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                         >> 0xfU))));
    vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = vlSelf->my_DE_stage__DOT____Vxrand_h8d9668fa__0;
    if ((((((((((((1U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                  | (2U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                 | (3U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                | (4U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
               | (5U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
              | (6U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
             | (7U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
            | (8U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
           | (9U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
          | (0xaU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
         | (0xbU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 1U;
    } else if ((((((((((((0x22U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                         | (0x23U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                        | (0xcU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                       | (0xdU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                      | (0xeU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                     | (0xfU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                    | (0x10U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                   | (0x11U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                  | (0x17U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                 | (0x1aU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                | (0x1bU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 2U;
    } else if ((((0x12U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                 | (0x13U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                | (0x14U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 2U;
    } else if (((0x15U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                | (0x16U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 2U;
    } else if ((0x18U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 3U;
    } else if ((0x19U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 4U;
    } else if (((((((0x1cU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)) 
                    | (0x1dU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                   | (0x1eU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                  | (0x1fU == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                 | (0x20U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE))) 
                | (0x21U == (IData)(vlSelf->__PVT__my_DE_stage__DOT__op_I_DE)))) {
        vlSelf->__PVT__my_DE_stage__DOT__type_I_DE = 3U;
    }
    __Vtableidx1 = vlSelf->__PVT__my_DE_stage__DOT__type_I_DE;
    vlSelf->__PVT__my_DE_stage__DOT__use_rs1_DE = Vpipeline__ConstPool__TABLE_hedfdecc6_0
        [__Vtableidx1];
    vlSelf->__PVT__my_DE_stage__DOT__use_rs2_DE = Vpipeline__ConstPool__TABLE_hca12deac_0
        [__Vtableidx1];
}

VL_INLINE_OPT void Vpipeline_pipeline___nba_sequent__TOP__pipeline__3(Vpipeline_pipeline* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpipeline_pipeline___nba_sequent__TOP__pipeline__3\n"); );
    // Body
    vlSelf->__PVT__from_DE_to_FE = ((((IData)(vlSelf->__PVT__my_DE_stage__DOT__use_rs1_DE) 
                                      & (vlSelf->__PVT__my_DE_stage__DOT__in_use_regs 
                                         >> (0x1fU 
                                             & (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                >> 0x17U)))) 
                                     | ((IData)(vlSelf->__PVT__my_DE_stage__DOT__use_rs2_DE) 
                                        & (vlSelf->__PVT__my_DE_stage__DOT__in_use_regs 
                                           >> (0x1fU 
                                               & ((vlSelf->__PVT__my_FE_stage__DOT__FE_latch[5U] 
                                                   << 4U) 
                                                  | (vlSelf->__PVT__my_FE_stage__DOT__FE_latch[4U] 
                                                     >> 0x1cU)))))) 
                                    | (IData)(vlSymsp->TOP__pipeline__my_AGEX_stage.__PVT__from_AGEX_to_DE));
}

VL_INLINE_OPT void Vpipeline_pipeline___nba_sequent__TOP__pipeline__4(Vpipeline_pipeline* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vpipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpipeline_pipeline___nba_sequent__TOP__pipeline__4\n"); );
    // Init
    CData/*0:0*/ __Vdlyvset__my_DE_stage__DOT__regs__v0;
    __Vdlyvset__my_DE_stage__DOT__regs__v0 = 0;
    CData/*4:0*/ __Vdlyvdim0__my_DE_stage__DOT__regs__v32;
    __Vdlyvdim0__my_DE_stage__DOT__regs__v32 = 0;
    IData/*31:0*/ __Vdlyvval__my_DE_stage__DOT__regs__v32;
    __Vdlyvval__my_DE_stage__DOT__regs__v32 = 0;
    CData/*0:0*/ __Vdlyvset__my_DE_stage__DOT__regs__v32;
    __Vdlyvset__my_DE_stage__DOT__regs__v32 = 0;
    // Body
    __Vdlyvset__my_DE_stage__DOT__regs__v0 = 0U;
    __Vdlyvset__my_DE_stage__DOT__regs__v32 = 0U;
    if (vlSymsp->TOP.reset) {
        __Vdlyvset__my_DE_stage__DOT__regs__v0 = 1U;
    } else if ((1U & (IData)((vlSymsp->TOP__pipeline__my_WB_stage.__PVT__from_WB_to_DE 
                              >> 0x25U)))) {
        __Vdlyvval__my_DE_stage__DOT__regs__v32 = (IData)(vlSymsp->TOP__pipeline__my_WB_stage.__PVT__from_WB_to_DE);
        __Vdlyvset__my_DE_stage__DOT__regs__v32 = 1U;
        __Vdlyvdim0__my_DE_stage__DOT__regs__v32 = 
            (0x1fU & (IData)((vlSymsp->TOP__pipeline__my_WB_stage.__PVT__from_WB_to_DE 
                              >> 0x20U)));
    }
    if (__Vdlyvset__my_DE_stage__DOT__regs__v0) {
        vlSelf->__PVT__my_DE_stage__DOT__regs[0U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[1U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[2U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[3U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[4U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[5U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[6U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[7U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[8U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[9U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xaU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xbU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xcU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xdU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xeU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0xfU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x10U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x11U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x12U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x13U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x14U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x15U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x16U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x17U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x18U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x19U] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1aU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1bU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1cU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1dU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1eU] = 0U;
        vlSelf->__PVT__my_DE_stage__DOT__regs[0x1fU] = 0U;
    }
    if (__Vdlyvset__my_DE_stage__DOT__regs__v32) {
        vlSelf->__PVT__my_DE_stage__DOT__regs[__Vdlyvdim0__my_DE_stage__DOT__regs__v32] 
            = __Vdlyvval__my_DE_stage__DOT__regs__v32;
    }
}
