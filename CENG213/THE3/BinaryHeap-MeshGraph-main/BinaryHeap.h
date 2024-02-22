#pragma once

#include <vector>

struct HeapElement
{
    int     uniqueId;
    double  weight;
};

class BinaryHeap
{
    private:
    std::vector<HeapElement> elements;
    void agaBuildHeapi(std::vector<HeapElement> adana){
        std::vector<HeapElement> depo1;
        for(int i=0;i<adana.size();i++){
            
            int iekle;
            double wekle; 
            PopHeap(iekle,wekle);
            HeapElement hekle;
            hekle.uniqueId=iekle;
            hekle.weight=wekle;
            depo1.push_back(hekle);
            
        }
        
        for(int i,t=0;t<adana.size();t++){
            Add(depo1[t].uniqueId,depo1[t].weight);
        }
        
    }
    
     public:
        // Constructors & Destructor
                            BinaryHeap();
        //
        bool                Add(int uniqueId, double weight);
        bool                PopHeap(int& outUniqueId, double& outWeight);
        bool                ChangePriority(int uniqueId, double newWeight);
        int                 HeapSize() const;

   
};
