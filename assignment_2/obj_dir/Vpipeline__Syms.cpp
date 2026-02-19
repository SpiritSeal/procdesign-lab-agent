// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vpipeline__pch.h"
#include "Vpipeline.h"
#include "Vpipeline___024root.h"
#include "Vpipeline_pipeline.h"
#include "Vpipeline_WB_STAGE.h"
#include "Vpipeline_AGEX_STAGE.h"

// FUNCTIONS
Vpipeline__Syms::~Vpipeline__Syms()
{
}

Vpipeline__Syms::Vpipeline__Syms(VerilatedContext* contextp, const char* namep, Vpipeline* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP__pipeline{this, Verilated::catName(namep, "pipeline")}
    , TOP__pipeline__my_AGEX_stage{this, Verilated::catName(namep, "pipeline.my_AGEX_stage")}
    , TOP__pipeline__my_WB_stage{this, Verilated::catName(namep, "pipeline.my_WB_stage")}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.pipeline = &TOP__pipeline;
    TOP__pipeline.my_AGEX_stage = &TOP__pipeline__my_AGEX_stage;
    TOP__pipeline.my_WB_stage = &TOP__pipeline__my_WB_stage;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__pipeline.__Vconfigure(true);
    TOP__pipeline__my_AGEX_stage.__Vconfigure(true);
    TOP__pipeline__my_WB_stage.__Vconfigure(true);
    // Setup scopes
    __Vscope_pipeline__my_AGEX_stage.configure(this, name(), "pipeline.my_AGEX_stage", "my_AGEX_stage", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_pipeline__my_WB_stage.configure(this, name(), "pipeline.my_WB_stage", "my_WB_stage", 0, VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_pipeline__my_AGEX_stage.varInsert(__Vfinal,"bp_correct_AGEX_reg", &(TOP__pipeline__my_AGEX_stage.bp_correct_AGEX_reg), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_pipeline__my_AGEX_stage.varInsert(__Vfinal,"bp_total_AGEX_reg", &(TOP__pipeline__my_AGEX_stage.bp_total_AGEX_reg), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_pipeline__my_WB_stage.varInsert(__Vfinal,"WB_counters", &(TOP__pipeline__my_WB_stage.WB_counters), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,1, 255,0);
        __Vscope_pipeline__my_WB_stage.varInsert(__Vfinal,"last_WB_value", &(TOP__pipeline__my_WB_stage.last_WB_value), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,1, 1023,0);
    }
}
