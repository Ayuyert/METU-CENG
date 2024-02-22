`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end

	// You can implement your code here
    // ...
    
    always@(posedge clk) begin
    if ((B == 0) && (H == 0) ) begin
    	Q = ~Q;
    end 
    else if ((B == 0) && (H == 1)) begin
    	Q = 1;
    end
    
    else if ((B == 1) && (H == 0) ) begin
    	Q = 0;
    end
    else if ((B == 1) && (H == 1) ) begin
    	Q = Q;
    end
    

    end

endmodule

module ic1337(// Inputs
              input A0,
              input A1,
              input A2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

	// You can implement your code here
    // ...
    

    
   
    
    bh m ((A0^!A1)|A2,(A0&!A2),clk,Q0);
    bh n (A0&(!A2), (!((!A0)|A1))&A2, clk, Q1);
    
 
    
    assign Z = ~(Q0^Q1) ;
   

endmodule
