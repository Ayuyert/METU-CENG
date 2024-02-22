#include "the3.h"

int dp[15811][15811];

std::string reverse(std::string& str){
    for(int i =0; i< str.length()/2; i++)
    {
        char temp = str[i];
        str[i]=str[str.length()-1-i];
        str[str.length()-1-i] = temp;
    }
    return str;
}

int rhelp(std::string& sequence_A, std::string& sequence_B, int gap, int mismatch, int match, std::string& possible_alignment, int i, int j, int& call_count) {
   call_count++;
    if (call_count >= 1000000) {
        possible_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }

     if (i == 0 || j == 0) {
        if (i == 0 && j == 0) return 0;
        return -gap * std::max(i, j);
    }

    int score = rhelp(sequence_A, sequence_B, gap, mismatch, match, possible_alignment, i - 1, j - 1, call_count);
    if (sequence_A[i - 1] != sequence_B[j - 1]) {
        score += 1*mismatch;
        possible_alignment += '!';
    } 
    else {
        score += match;
        possible_alignment += sequence_A[i - 1];
    }

    int score1 = rhelp(sequence_A, sequence_B, gap, mismatch, match, possible_alignment, i - 1, j, call_count) - gap;
    int score2 = rhelp(sequence_A, sequence_B, gap, mismatch, match, possible_alignment, i, j - 1, call_count ) - gap;

    if (score >= score1 && score >= score2) {
        return score;
    } 
    else if (score1 >= score && score1 >= score2) {
        if(call_count <1000000){
        possible_alignment += '_';
        return score1;}
        return 0;
    } 
    else {
        if(call_count <1000000){
        possible_alignment += '.';
        return score2;}
        return 0;
    }
}

int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count) {
    possible_alignment = "";
    call_count = 0;
    int result = rhelp(sequence_A, sequence_B, gap, mismatch, match, possible_alignment, sequence_A.length(), sequence_B.length(), call_count);
    if(possible_alignment != "STACK LIMIT REACHED" ) possible_alignment=reverse(possible_alignment);
    return result;
}

int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment) {
    int highest_alignment_score;
    int m = sequence_A.length();
    int n = sequence_B.length();
    bool flag1 = false; 
    bool flag2 = false;
   // int dp[m + 1][n + 1];
    
   
     for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0) 
            {
                dp[i][j] = -gap * std::max(i, j);
            } 
            
            else 
            {
                int score = 0;
                if(sequence_A[i - 1] == sequence_B[j - 1]) score = match;
                else score = -1*mismatch;
                dp[i][j] = std::max(dp[i - 1][j - 1] + score, std::max(dp[i - 1][j] - gap, dp[i][j - 1] - gap));
            }
        }
    }

    int i = m, j = n;
    possible_alignment = "";
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0) {
            int aga;
            if(sequence_A[i - 1] == sequence_B[j - 1]) aga = match;
            else aga = -1*mismatch;
            if(dp[i][j] == dp[i - 1][j - 1] + aga){
            if(sequence_A[i - 1] == sequence_B[j - 1]) possible_alignment += sequence_A[i - 1];
            else possible_alignment +='!';
            
            i--;
            j--;
            flag1 = true;
            }
        } 
        
        if (i > 0 && dp[i][j] == dp[i - 1][j] - gap  && !flag1) {
            possible_alignment += '.';
            i--;
        } 
        
        else if(!flag1) {
            possible_alignment += '_';
            j--;
        }
        flag1 = false;
    }

   possible_alignment=reverse(possible_alignment);
   highest_alignment_score = dp[m][n];
    return highest_alignment_score;
}
