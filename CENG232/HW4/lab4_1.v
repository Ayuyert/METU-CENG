`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);

	initial  dataOut = 0;

  always @* begin
	if (addr ==0) dataOut = 0; 
	else if (addr ==1) begin dataOut = 85;end
	else if (addr ==2) begin dataOut = 170;end
	else if (addr ==3) begin dataOut = 51;end
	else if (addr ==4) begin dataOut = 204;end
	else if (addr ==5) begin dataOut = 15;end
	else if (addr ==6) begin dataOut = 240;end
	else if (addr ==7) begin dataOut = 255;end
	else dataOut =0;
  end



endmodule

module Difference_RAM (
input mode,
input [2:0] addr,
input [7:0] dataIn,
input [7:0] mask,
input CLK,
output reg [7:0] dataOut);
	
	reg [7:0] odevihazirlayan [7:0];
	initial begin
	
		odevihazirlayan[0]=0 ;
	        dataOut = 0;
	        odevihazirlayan[1]=0 ;
	        odevihazirlayan[2]=0 ;
	        odevihazirlayan[3]=0 ;
	        odevihazirlayan[4]=0 ;
	        odevihazirlayan[5]=0 ;
	        odevihazirlayan[6]=0 ;
	        odevihazirlayan[7]=0 ;
	        
	        
	    end
	
	always @(*) begin
		if(mode == 1) begin
			dataOut =odevihazirlayan[addr]; 
	
		end	
		end
   always@(posedge CLK) begin
	
	
	    
	if (mode == 0) begin
	
		if(dataIn<mask ) begin odevihazirlayan[addr] = mask-dataIn ;end
		else begin odevihazirlayan[addr] =dataIn-mask;end
		
		
	
	end
	
   end
	



endmodule


module EncodedMemory (
input mode,
input [2:0] index,
input [7:0] number,
input CLK,
output [7:0] result);

	wire [7:0] mask;

	ROM R(index, mask);
	Difference_RAM DR(mode, index, number, mask, CLK, result);

endmodule


