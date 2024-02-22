#include "BinaryHeap.h"
#include <iostream>
BinaryHeap::BinaryHeap()
{
   
    elements.resize(1);
    elements[0].weight=-99;
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    int k = elements.size();
    for(int i=1;i<k;i++){
        if (uniqueId==elements[i].uniqueId) return false;
    }
    
    int boy=elements.size();
    elements.resize(boy+1);
    elements[boy].uniqueId=uniqueId;
    elements[boy].weight=weight;
    
    while(boy>=2){
        if(elements[boy].weight<elements[(boy)/2].weight){
            int tempid=elements[boy].uniqueId;
            double tempw=elements[boy].weight;
            elements[boy].weight=elements[(boy)/2].weight;
            elements[boy].uniqueId=elements[(boy)/2].uniqueId;
            elements[(boy)/2].uniqueId=tempid;
            elements[(boy)/2].weight=tempw;
        }
        (boy)/=2;
    }
    
    
    
    
    return true;
    
 
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
   //std::cout<<"\n";
    // TODO:
    if(elements.size()==1) return false;
    //std::cout<<"Printing the initial:\n";
    /*for (int p=0; p<elements.size();p++){
            std::cout<<elements[p].weight<<" ";
        }*/
       // std::cout<<"\n";
    outUniqueId=elements[1].uniqueId;
    outWeight=elements[1].weight;
    elements[1].uniqueId=elements[elements.size()-1].uniqueId;
    elements[1].weight=elements[elements.size()-1].weight;
    elements.resize(elements.size()-1);
    int k=1;
    int melike=0;
    while(k<double(elements.size())/2 && (elements[k].weight>elements[2*k].weight||elements[k].weight>elements[2*k+1].weight)){
        if(elements.size()>(2*k+1) && elements[2*k].weight>elements[2*k+1].weight){
            melike=-1;
        }
        else melike=0;
       
            int tempid=elements[k].uniqueId;
            int tempw=elements[k].weight;
            elements[k].uniqueId=elements[2*k-melike].uniqueId;
            elements[k].weight=elements[2*k-melike].weight;
            elements[2*k-melike].uniqueId=tempid;
            elements[2*k-melike].weight=tempw;
            
        
        
        
        k*=2;
        k=k-melike;
    }
    
    if(k==elements.size()/2 && elements[k].weight>elements[2*k].weight){
        int tempid=elements[k-melike].uniqueId;
            int tempw=elements[k-melike].weight;
        elements[k-melike].uniqueId=elements[2*k-melike].uniqueId;
            elements[k-melike].weight=elements[2*k-melike].weight;
            elements[2*k-melike].uniqueId=tempid;
            elements[2*k-melike].weight=tempw;
        
    }
    
   //std::cout<<"Printing in loop:\n";
        /*for(int p=1; p<elements.size();p++){
            std::cout<<elements[p].weight<<" ";
        }
        std::cout<<"\n";*/
    
    return true;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    
    int k = elements.size();
    for(int i=1;i<k;i++){
        if(uniqueId==elements[i].uniqueId){
            
            elements[i].weight=newWeight;
            agaBuildHeapi(elements);
            return true;
        }
    }
    
    
    
    return false;
}

int BinaryHeap::HeapSize() const
{
    return elements.size()-1;
  
}
