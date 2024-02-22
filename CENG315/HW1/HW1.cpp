#include "the1.h"

//You may write your own helper functions here
int Sort(unsigned short ary[3],int aryi[3]){
    bool swapped = true;
    while (swapped){
        swapped = false;
        for(int t=0; t<2 ; t++){
            if(ary[t]>ary[t+1]){
                unsigned short temp;
                temp = ary[t];
                ary[t] = ary[t+1];
                ary[t+1] = temp;
                int tempe = aryi[t];
                aryi[t] = aryi[t+1];
                aryi[t+1] = tempe;
                swapped =true;
            }
        }
    }
    return aryi[1];
}
int FindPivot(unsigned short* arr,  int size){
    
    unsigned short c1 = arr[0];
    unsigned short c2 = arr[size-1];
    unsigned short c3 = arr[(size-1)/2];
    if(c1==c2 || c2==c3 || c1==c3) return -1;
    unsigned short ary[3] = {c1,c2,c3};
    int aryi[3] = {0,size-1, (size-1)/2 };
    return Sort(ary, aryi);
    
}
double avg(int s){
    if (s<0) return -1*s;
    return s;
}
void Swap(unsigned short* arr, int i, int j, double& max_dist, double& avg_dist,long& swap){
    unsigned short temp;
    avg_dist += avg(i-j);
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    if(avg(j-i)>max_dist) max_dist = avg(j-i);
    swap= swap+1;
}
int Hpartition(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3 ,int size){
    if(median_of_3){
        int pos = FindPivot(arr, size);
        if(pos!= (size-1)/2 && pos != -1){
        Swap(arr,pos,(size-1)/2, max_dist,avg_dist,swap);
        }
       
    }
    unsigned short x = arr[(size-1)/2];
    int i=-1, j=size;
    
    while(1){
        do{j--; }while (arr[j]<x);
        do{i++;}while (arr[i]>x);
        if(i<j) {
        Swap(arr,i,j,max_dist,avg_dist,swap); 
        
        
        }
        
        else return j;
    }
}
int HoareSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3 ,int size, int& recnum){
    //baştan sondan
    recnum++;
   
    if (size>1){
        int p = Hpartition(arr, swap, avg_dist,  max_dist, median_of_3, size);
        HoareSort(arr, swap, avg_dist,  max_dist, median_of_3, p+1, recnum);
        HoareSort(&arr[p+1], swap, avg_dist,  max_dist, median_of_3, size-1-p, recnum);
    }
    
    return recnum;
}

int Lpartition(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3 ,int size){
    if(median_of_3 && size>= 3){
        int pos = FindPivot(arr, size);
        if(pos!= (size-1) && pos != -1) {
        Swap(arr,pos,size-1,max_dist,avg_dist,swap);
        }
        
    }
    unsigned short x = arr[size-1];
    int i=-1;
    for(int j=0; j<size-1; j++){
        if(arr[j]>=x) {
            i++;
            Swap(arr,i,j,max_dist,avg_dist,swap);
            
        }
    }
    Swap(arr,i+1,size-1,max_dist,avg_dist,swap);
    
    return i+1;
    
}

int LSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3 ,int size, int& recnum){
    recnum++;
    if(size>1){
        int p = Lpartition(arr, swap, avg_dist,  max_dist, median_of_3, size);
        LSort(arr, swap, avg_dist,  max_dist, median_of_3, p, recnum);
        LSort(arr+p+1, swap, avg_dist,  max_dist, median_of_3, size-p-1, recnum);
    }
    return recnum;
}

int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){
    //Your code here
    int recnu = 0;
    int& recnum = recnu;
    if(hoare) {
        
        HoareSort(arr, swap, avg_dist,  max_dist, median_of_3, size ,recnum);
        
        avg_dist =double(avg_dist / swap);
        
        return recnum;
        
    }
    else 
    {
      
        LSort(arr, swap, avg_dist,  max_dist, median_of_3, size, recnum);
        
        avg_dist =double(avg_dist / swap);
        
        return recnum;
    }
    
}
