#include "the7.h"

// do not add extra libraries here

void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores){
                              
    
    int sizea = network.size();
    float son = 100000000;
    int maxdis = 0;
    std::vector<std::vector<int>> mesafe(sizea, std::vector<int>(sizea, son));
    infection_scores.resize(sizea);

    for(int i = 0; i < sizea; i++)
    {
        mesafe[i][i] = 0;
        
        for(auto &edge : network[i])
        {
            int w = edge.second;
            int j = edge.first;
            
            mesafe[i][j] = w;
        }
    }

    for(int k = 0; k < sizea; k++) {
        
        for(int i = 0; i < sizea; i++) {
            
            for(int j = 0; j < sizea; j++) {
                
                if(mesafe[k][j] < son && mesafe[i][k] <= son-1 && mesafe[i][j] > mesafe[i][k] + mesafe[k][j]) mesafe[i][j] = mesafe[i][k] + mesafe[k][j];
            }
        }
    }

    
    for(int i = 0; i < sizea; i++) {
        
        for(int j = 0; j < sizea; j++) {
            
            if(i != j && mesafe[i][j] != son) maxdis = std::max(maxdis, mesafe[i][j]);
        }
    }

    
    for(int i = 0; i < sizea; i++) {
        
        float sum = 0;
        
        for(int j = 0; j < sizea; j++) {
            
            if(i != j) {
                
                if(mesafe[i][j] ==son){
                    
                    sum = sum + maxdis +1;
                }
                
                else sum += mesafe[i][j];
                
            }
        }
        
        infection_scores[i] = (sizea - 1) / sum;
    }
}
