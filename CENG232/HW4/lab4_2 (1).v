`timescale 1ns / 1ps
module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, // 00:Air 01:Fire, 10:Earth, 11: Water
	input CLK,
	output reg [1:0] ballotBoxId,
	output reg [5:0] numberOfRegisteredVoters,
	output reg [5:0] numberOfVotesWinner, // number of votes of winner
	output reg [1:0] WinnerId,
	output reg AlreadyRegistered,
	output reg AlreadyVoted,
	output reg NotRegistered,
	output reg VotingHasNotStarted,
	output reg RegistrationHasEnded
	);
	integer kazanan;
	integer voters;
	integer votersair;
	integer votersearth;
	integer votersfire;
	integer voterswater;
	reg [1:0] oylar [63:0];
	integer a;
	integer counter;
	reg[1:0] kazananid;
	initial begin
		
		kazananid=0;
		kazanan = 0;
		voters = 0;
		votersair = 0;
		votersearth = 0;
		votersfire = 0;
		voterswater = 0;
		AlreadyRegistered = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0;
		ballotBoxId =0;
		numberOfRegisteredVoters = 0;
		numberOfVotesWinner = 0;
		WinnerId = 0;
		counter = 0;
		AlreadyVoted = 0;
		for(a=0;a<64;a=a+1) begin
			oylar [a] = 0;	
		end

	end
	always @(posedge CLK)
	begin
		AlreadyRegistered = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0;
		ballotBoxId = userID[5:4];
		counter = counter+1;
		AlreadyVoted = 0;
		if(counter<=100 && mode == 0)begin
			if(oylar[userID] == 0) begin oylar[userID] = 1; numberOfRegisteredVoters = numberOfRegisteredVoters+1;end
			else if(oylar[userID] == 1) AlreadyRegistered = 1;
		end
		if(counter<=100 && mode == 1) VotingHasNotStarted =1 ;
		if(counter>100 && counter <=200 && mode ==0) RegistrationHasEnded = 1;
		if(counter>100 && counter <=200 && mode ==1)begin
			if(oylar[userID] == 0) NotRegistered=1;
			else if(oylar[userID] == 1)begin
				if(candidate == 0)begin
						votersair=votersair+1;
						oylar[userID] =2;
						
					end
				else if(candidate == 1)begin
						votersfire=votersfire+1;
						oylar[userID] =2;

					end
				else if(candidate == 2)begin
						voterswater=voterswater+1;
						oylar[userID] =2;
					end
				else if(candidate == 3)begin
						votersearth=votersearth+1;
						oylar[userID] =2;
					end
			end
			else if(oylar[userID]==2) AlreadyVoted = 1;
			ballotBoxId = userID[5:4];
		end
		if(counter > 200)begin
			kazanan = votersair;
			kazananid = 0;
			if(votersfire>kazanan) begin kazanan = votersfire; kazananid=1; end
			if(voterswater>kazanan) begin kazanan = voterswater; kazananid=2; end
			if(votersearth>kazanan) begin kazanan = votersearth; kazananid=3; end
			WinnerId = kazananid;
			numberOfVotesWinner = kazanan;



		end
	end

endmodule
