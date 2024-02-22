#include "the4.h"

// do not add extra libraries here
int dp[1000][1000] = {INT_MAX};
int divide_land(int X, int Y, bool** possible_plots){

    for (int i = 0; i < X+1; i++) {
        for (int j = 0; j < Y+1; j++) {
            if (possible_plots[i][j]) dp[i][j] = 0;
            else dp[i][j] = i * j;
            
        }
    }
    for (int x = 1; x < X+1; x++) {
        x++;
        for (int y = 1; y < Y+1; y++) {
            y++;
            for (int i = 1; i < x; ++i) {
                if (dp[x][y] > dp[i][y] + dp[x-i][y]) dp[x][y] = dp[i][y] + dp[x-i][y];
            }
            
              for (int j = 1; j < y; ++j) {
                if (dp[x][y] > dp[x][j] + dp[x][y-j])  dp[x][y] = dp[x][j] + dp[x][y-j];
                
            }
            y--;
        }
        x--;
    }
    return dp[X][Y];}
