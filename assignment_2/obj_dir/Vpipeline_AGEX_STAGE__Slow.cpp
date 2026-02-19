// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpipeline.h for the primary calling header

#include "Vpipeline__pch.h"
#include "Vpipeline_AGEX_STAGE.h"
#include "Vpipeline__Syms.h"

void Vpipeline_AGEX_STAGE___ctor_var_reset(Vpipeline_AGEX_STAGE* vlSelf);

Vpipeline_AGEX_STAGE::Vpipeline_AGEX_STAGE(Vpipeline__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpipeline_AGEX_STAGE___ctor_var_reset(this);
}

void Vpipeline_AGEX_STAGE::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vpipeline_AGEX_STAGE::~Vpipeline_AGEX_STAGE() {
}
