`timescale 1ns / 1ps
module lab3_2(
			input[5:0] money,
			input CLK,
			input vm, //0:VM0, 1:VM1
			input [2:0] productID, //000:sandwich, 001:chocolate, 11x: dont care
			input sugar, //0: No sugar, 1: With Sugar
			output reg [5:0] moneyLeft,
			output reg [4:0] itemLeft,
			output reg productUnavailable,//1:show warning, 0:do not show warning
			output reg insufficientFund , //1:full, 0:not full
			output reg notExactFund , //1:full, 0:not full
			output reg invalidProduct, //1: empty, 0:not empty
			output reg sugarUnsuitable, //1: empty, 0:not empty
			output reg productReady	//1:door is open, 0:closed
	);

	// Internal State of the Module
	// (you can change this but you probably need this)
	reg [4:0] numOfSandwiches;
	reg [4:0] numOfChocolate;
	reg [4:0] numOfWaterVM1;
	reg [4:0] numOfWaterVM2;
	reg [4:0] numOfCoffee;
	reg [4:0] numOfTea;

	initial
	begin
		// You can initialize here
    	// ...
    	numOfSandwiches = 10;
    	numOfChocolate = 10;
    	numOfWaterVM1 = 5;
    	numOfWaterVM2 = 10;
    	numOfCoffee = 10;
    	numOfTea = 10;
	end

	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin

		// You can implement your code here
    	// ...
    	itemLeft = 0;
    	productUnavailable = 0;
    	insufficientFund = 0;
    	notExactFund = 0;
    	invalidProduct = 0;
    	sugarUnsuitable = 0;
    	productReady = 0;
		moneyLeft = money;
    	 if ((vm == 0) && (productID == 0) && money == 20 && numOfSandwiches > 0)
    		begin
    			moneyLeft = 0;
    			productUnavailable = 0;
    			itemLeft = numOfSandwiches -1;
    			notExactFund = 0;
    			invalidProduct = 0;
    			productReady = 1;
    			numOfSandwiches = itemLeft;
    			insufficientFund = 0;
    		end 
    	else if ((vm == 0) && (productID == 0) && numOfSandwiches == 0)
    		begin
    			productUnavailable = 1;
    			productReady = 0;
    			invalidProduct = 0;
    			
    		end 
    		
    	else if ((vm == 0) && (productID == 0) && money != 20)
    		begin
    			notExactFund = 1;
    			invalidProduct = 0;
    			productReady = 0;
    			
    		end
    		
    	///////////////////////////////////////////////////////////////////////	
    		
    	else if ((vm == 0) && (productID == 1) && money == 10 && numOfChocolate > 0)
    		begin
    			moneyLeft = 0;
    			productUnavailable = 0;
    			itemLeft = numOfChocolate -1;
    			notExactFund = 0;
    			invalidProduct = 0;
    			productReady = 1;
    			numOfChocolate = itemLeft;
    			insufficientFund = 0;
    			
    		end 
    	else if ((vm == 0) && (productID == 1) && numOfChocolate == 0)
    		begin
    			productUnavailable = 1;
    			productReady = 0;
    			invalidProduct = 0;
    			
    		end 
    		
    	else if ((vm == 0) && (productID == 1) && money != 10)
    		begin
    			notExactFund = 1;
    			invalidProduct = 0;
    			productReady = 0;
    			
    		end
    		
    	
    	/////////////////////////////////////////////////////////////////////
    	
    	else if ((vm == 0) && (productID == 2) && money == 5 && numOfWaterVM1 > 0)
    		begin
    			moneyLeft = 0;
    			productUnavailable = 0;
    			numOfWaterVM1--;
    			notExactFund = 0;
    			invalidProduct = 0;
    			productReady = 1;
				itemLeft = numOfWaterVM1;
    			insufficientFund = 0;
    		end 
    	else if ((vm == 0) && (productID == 2) && numOfWaterVM1== 0)
    		begin
    			productUnavailable = 1;
    			productReady = 0;
    			invalidProduct = 0;
    			
    		end 
    		
    	else if ((vm == 0) && (productID == 2) && money != 5)
    		begin
    			notExactFund = 1;
    			invalidProduct = 0;
    			productReady = 0;
    			
    		end
    		
    	
    	///////////////////////////////////////////////////////////////////////////
    	
    	 else if ((vm == 1) && (productID == 2) && money >= 5 && numOfWaterVM2 > 0 && sugar==0)
    		begin
    			productUnavailable = 0;
    			moneyLeft = money - 5;
    			numOfWaterVM2 = numOfWaterVM2 - 1;
    			itemLeft = numOfWaterVM2 - 1;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 1;
    		end
    	
    	else if ((vm == 1) && (productID == 2) && numOfWaterVM2 > 0 && sugar==1 || vm == 0)
    		begin	
    			productUnavailable = 0;
    			invalidProduct = 0;
    			sugarUnsuitable = 1;
    			productReady = 0;
				moneyLeft = money;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 2) &&  numOfWaterVM2 <= 0 )
    		begin
    			productUnavailable = 1;
    			invalidProduct = 0;
    			productReady = 0;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 2) && money < 5)
    		begin	
    			productUnavailable = 0;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 0;
    			insufficientFund = 1;
    		end
    	
    	/////////////////////////////////////////////////////////////////////////////////////////
    	
    	else if ((vm == 1) && (productID == 3) && money >= 12 && numOfCoffee > 0 )
    		begin	
    			productUnavailable = 0;
    			moneyLeft = money - 12;
    			numOfCoffee = numOfCoffee - 1;
    			itemLeft = numOfCoffee;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 1;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 3) &&  numOfCoffee <= 0 )
    		begin
    			productUnavailable = 1;
    			invalidProduct = 0;
    			productReady = 0;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 3) && money < 12)
    		begin	
    			productUnavailable = 0;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 0;
    			insufficientFund = 1;
    		end
    		
    	///////////////////////////////////////////////////////////////////////////////////////////////
    	
    	else if ((vm == 1) && (productID == 4) && money >= 8 && numOfTea > 0 )
    		begin	
    			productUnavailable = 0;
    			moneyLeft = money - 8;
    			numOfWaterVM2 = numOfTea - 1;
    			itemLeft = numOfTea;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 1;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 4) &&  numOfTea <= 0 )
    		begin
    			productUnavailable = 1;
    			invalidProduct = 0;
    			productReady = 0;
    		end
    	
    	
    	else if ((vm == 1) && (productID == 4) && money < 8)
    		begin	
    			productUnavailable = 0;
    			invalidProduct = 0;
    			sugarUnsuitable = 0;
    			productReady = 0;
    			insufficientFund = 1;
    		end
    	
    	else if ((vm == 0) && ((productID != 0) || (productID != 1) || (productID != 2)))
    		begin
    			invalidProduct = 1;
    		
    		end
    		
    	else if ((vm == 1) && ((productID != 4) || (productID != 3) || (productID != 2)))
    		begin
    			invalidProduct = 1;
    		end
    	
    	
    	
    	
    	
	end


endmodule



