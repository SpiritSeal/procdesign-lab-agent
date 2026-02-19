 `include "define.vh" 


module FE_STAGE(
  input wire clk,
  input wire reset,
  input wire [`from_DE_to_FE_WIDTH-1:0] from_DE_to_FE,
  input wire [`from_AGEX_to_FE_WIDTH-1:0] from_AGEX_to_FE,   
  input wire [`from_MEM_to_FE_WIDTH-1:0] from_MEM_to_FE,   
  input wire [`from_WB_to_FE_WIDTH-1:0] from_WB_to_FE, 
  output wire [`FE_latch_WIDTH-1:0] FE_latch_out
);

  `UNUSED_VAR (from_MEM_to_FE)
  `UNUSED_VAR (from_WB_to_FE)

  // I-MEM
  (* ram_init_file = `IDMEMINITFILE *)
  reg [`DBITS-1:0] imem [`IMEMWORDS-1:0];
 
  initial begin
      $readmemh(`IDMEMINITFILE , imem);
  end

  /* pipeline latch */ 
  reg [`FE_latch_WIDTH-1:0] FE_latch;  // FE latch 
  wire valid_FE;
   
  reg [`DBITS-1:0] PC_FE_latch; // PC latch in the FE stage   
  
  reg [`DBITS-1:0] inst_count_FE; /* for debugging purpose */ 
  
  wire [`INSTBITS-1:0] inst_FE;  // instruction value in the FE stage 
  wire [`DBITS-1:0] pcplus_FE;  // pc plus value in the FE stage 
  wire stall_pipe_FE; // signal to indicate when a front-end needs to be stall
  
  wire [`FE_latch_WIDTH-1:0] FE_latch_contents;  // the signals that will be FE latch contents 
  
  // reading instruction from imem 
  assign inst_FE = imem[PC_FE_latch[`IMEMADDRBITS-1:`IMEMWORDBITS]];  
  
  // wire to send the FE latch contents to the DE stage 
  assign FE_latch_out = FE_latch; 
 
  assign pcplus_FE = PC_FE_latch + `INSTSIZE;
  
  assign valid_FE = 1'b1;

  wire br_mispred_AGEX;  
  wire [`DBITS-1:0] br_target_AGEX;  
  wire update_btb_pht_AGEX;
  wire actual_taken_AGEX;
  wire [`DBITS-1:0] PC_AGEX;
  wire [7:0] pht_idx_AGEX;

  assign {
    br_mispred_AGEX,
    br_target_AGEX,
    update_btb_pht_AGEX,
    actual_taken_AGEX,
    PC_AGEX,
    pht_idx_AGEX
  } = from_AGEX_to_FE;

  assign stall_pipe_FE = from_DE_to_FE[0];

  // Branch Predictor structures
  reg [7:0] BHR;
  reg [1:0] PHT [255:0];
  reg valid_BTB [15:0];
  reg [25:0] tag_BTB [15:0];
  reg [31:0] target_BTB [15:0];

  integer i;
  always @(posedge clk) begin
    if (reset) begin
      BHR <= 8'b0;
      for (i = 0; i < 256; i = i + 1) PHT[i] = 2'b01;
      for (i = 0; i < 16; i = i + 1) valid_BTB[i] = 1'b0;
    end else if (update_btb_pht_AGEX) begin
      // Update BHR
      BHR <= {BHR[6:0], actual_taken_AGEX};
      // Update PHT
      if (actual_taken_AGEX) begin
        if (PHT[pht_idx_AGEX] != 2'b11) PHT[pht_idx_AGEX] <= PHT[pht_idx_AGEX] + 2'b01;
      end else begin
        if (PHT[pht_idx_AGEX] != 2'b00) PHT[pht_idx_AGEX] <= PHT[pht_idx_AGEX] - 2'b01;
      end
      // Update BTB
      valid_BTB[PC_AGEX[5:2]] <= 1'b1;
      tag_BTB[PC_AGEX[5:2]] <= PC_AGEX[31:6];
      target_BTB[PC_AGEX[5:2]] <= br_target_AGEX;
    end
  end

  // Prediction Logic
  wire [7:0] pht_idx_FE = PC_FE_latch[9:2] ^ BHR;
  wire [3:0] btb_idx_FE = PC_FE_latch[5:2];
  wire btb_hit_FE = valid_BTB[btb_idx_FE] && (tag_BTB[btb_idx_FE] == PC_FE_latch[31:6]);
  wire pht_taken_FE = PHT[pht_idx_FE][1];
  
  wire pred_taken_FE = btb_hit_FE && pht_taken_FE;
  wire [`DBITS-1:0] pred_next_PC_FE = pred_taken_FE ? target_BTB[btb_idx_FE] : pcplus_FE;

  assign FE_latch_contents = {
                                valid_FE, 
                                inst_FE, 
                                PC_FE_latch, 
                                pcplus_FE, 
                                inst_count_FE,
                                pred_next_PC_FE,
                                pht_idx_FE
                                };

  always @ (posedge clk) begin
   if (reset) begin 
      PC_FE_latch <= `STARTPC;
      inst_count_FE <= 1;
    end else if (br_mispred_AGEX) begin
      PC_FE_latch <= br_target_AGEX;
    end else if (stall_pipe_FE) begin
      PC_FE_latch <= PC_FE_latch; 
    end else begin 
      PC_FE_latch <= pred_next_PC_FE;
      inst_count_FE <= inst_count_FE + 1; 
    end 
  end
  

  always @ (posedge clk) begin
    if (reset) begin 
      FE_latch <= '0; 
    end else begin 
      if (br_mispred_AGEX)
        FE_latch <= '0;
      else if (stall_pipe_FE)
        FE_latch <= FE_latch; 
      else 
        FE_latch <= FE_latch_contents; 
    end  
  end

endmodule
