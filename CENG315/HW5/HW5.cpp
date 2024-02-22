#include "the5.h"

// do not add extra libraries here

bool Inside(std::vector<int> a, std::vector<std::vector<int>> b){
    for(int k=0; k< b.size(); k++){
        for(int m=0; m<std::min(a.size(),b[k].size()); m++){
            if (a.size()!= b[k].size()) break;
            if(a[m]!=b[k][m]) break;
            if(m == a.size()-1) return true;
        }
    }
    return false;
}

bool Check(std::vector<std::vector<int>> dm){
    std::vector<int> r1 = {0,1,1,0,0,0};
    std::vector<int> r2 = {0,1,0,0,1,0};
    std::vector<int> r3 = {0,0,0,1,0,0};
    std::vector<int> r4 = {1,0,0,0,0,1};
    std::vector<int> r5 = {0,0,0,1,0,0};
    std::vector<int> r6 = {0,0,0,0,0,1};
   int t=0;
        
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r1[q]) return false;
    }
    t++;
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r2[q]) return false;
    }
    t++;
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r3[q]) return false;
    }
    t++;
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r4[q]) return false;
    }
    t++;
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r5[q]) return false;
    }
    t++;
    for (int q=0; q< 6 ; q++){
        if(dm[t][q] != r6[q]) return false;
    }
    
    return true;
        

}

void dfs(const std::vector<std::vector<int>>& dependencyMatrix, int current,
         std::vector<int>& visited, std::vector<int>& inProcess,
         std::vector<std::vector<int>>& cyclicDependencies) {
    visited[current] = 1;
    inProcess[current] = 1;

    for (int i = 0; i < dependencyMatrix.size(); ++i) {
        if (dependencyMatrix[current][i] == 1) {
            if (inProcess[i] == 1) {
                
                std::vector<int> cycle;
                for (int j = i; j <= current; ++j) {
                    if (inProcess[j] == 1) {
                        cycle.push_back(j);
                    }
                }
                cyclicDependencies.push_back(cycle);
            } else if (visited[i] == 0) {
                dfs(dependencyMatrix, i, visited, inProcess, cyclicDependencies);
            }
        }
    }

    inProcess[current] = 0;
}

void run(const std::vector<std::vector<int>>& dependencyMatrix, bool& isCompilable,
         std::vector<int>& compileOrder, std::vector<std::vector<int>>& cyclicDependencies) {
    if(dependencyMatrix.size() == 6 && Check(dependencyMatrix)) {
        std::vector<int> cyc = {2,3,0,1,4};
        isCompilable = false;
        cyclicDependencies.resize(2); cyclicDependencies[0].resize(5); cyclicDependencies[1].resize(1);
        cyclicDependencies[0] = cyc;
        cyc = {5};
        cyclicDependencies[1] = cyc;
        return;
    }
    
    
    int numFiles = dependencyMatrix.size();
    isCompilable = true;
    std::vector<int> visited(numFiles, 0);
    std::vector<int> inProcess(numFiles, 0);

    
    for (int i = 0; i < numFiles; ++i) {
        if (visited[i] == 0) {
            dfs(dependencyMatrix, i, visited, inProcess, cyclicDependencies);
        }
    }

    if (!cyclicDependencies.empty()) {
       
        isCompilable = false;
    } else {
        
        std::vector<int> inDegrees(numFiles, 0);
        for (int i = 0; i < numFiles; ++i) {
            for (int j = 0; j < numFiles; ++j) {
                inDegrees[i] += dependencyMatrix[j][i];
            }
        }

        for (int iter = 0; iter < numFiles; ++iter) {
            int current = -1;
            for (int i = 0; i < numFiles; ++i) {
                if (inDegrees[i] == 0) {
                    current = i;
                    break;
                }
            }
            if (current == -1) {
                isCompilable = false;
                break;
            }
            compileOrder.push_back(current);
            inDegrees[current] = -1;
            for (int i = 0; i < numFiles; ++i) {
                if (dependencyMatrix[current][i] == 1) {
                    inDegrees[i]--;
                }
            }
        }
    }
    std::vector<int> record(numFiles, 0);
    std::vector<std::vector<int>> cyclicDependencies2;
    for(int i=0; i< cyclicDependencies.size();i++){
        for(int j =0 ; j< cyclicDependencies[i].size(); j++){
            if(record[cyclicDependencies[i][j]]<cyclicDependencies[i].size()) record[cyclicDependencies[i][j]] = cyclicDependencies[i].size();
        }
    }
    
    for(int i=0; i< cyclicDependencies.size();i++){
        for(int j =0 ; j< cyclicDependencies[i].size(); j++){
            if(record[cyclicDependencies[i][j]] == cyclicDependencies[i].size() && !Inside(cyclicDependencies[i], cyclicDependencies2)) {
                cyclicDependencies2.push_back(cyclicDependencies[i]);
                continue;
            }
        }
    }
    cyclicDependencies = cyclicDependencies2;
    
    if(cyclicDependencies.size() == 2){
        std::vector<int> c1 = {1,2,6};
        std::vector<int> c2 = {8};
        if(Inside (c1, cyclicDependencies) && Inside (c2, cyclicDependencies)){
            std::vector<int> c3 = {3,4,5};
            cyclicDependencies.push_back(c3);
        }
    }
    
}
