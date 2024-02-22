#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/

int maxStr(std::string* arr, int size){
    int max=0;
    for(int k=0;k<size;k++){
       if(arr[k].size()>max) max = arr[k].size(); 
    }
    return max;
}

std::string* reverse(std::string* ary, int size){
    std::string* temp = new std::string[size];
    for(int y=0; y<size;y++){
        temp[size-1-y] = ary[y];
    }
    for(int y=0; y<size;y++){
        ary[y]= temp[y];
    }
    return ary;
}
std::string* countingSort(std::string* arr, int size, int order, int& counter){
    int range = 26;
    std::string* B = new std::string[size+1];
    int* C = new int[range+1];
    for(int i =0; i<range+1;i++){
        C[i] = 0;
    }
    for(int j=1; j< size+1; j++){counter++;
        if(arr[j].size()<=order) C[0]++;
        else C[arr[j][order]-64]+=1;
      
    }
    
    for(int i= 1; i<range+1; i++){
        C[i] = C[i] + C[i-1];
        counter++;
    }
    
    for(int j = size; j>0; j--){
        if(arr[j].size()<=order){
            
            B[C[0]] = arr[j];
            C[0] -=1;
            
        }
        else{
            
            B[C[arr[j][order]-64]] = arr[j];
            C[arr[j][order]-64]-=1;
        
        }
        counter++;
    }
    
    for (int i = 1; i <= size; i++) {
        arr[i] = B[i];
        counter++;
    }
    
    return arr;
    
}

int radix_string_sort(std::string* arr, int size, bool ascending){
    int counter=0;
    std:: string* A = arr-1;
    int maxS = maxStr(arr,size); 
    for(int hasan = maxS-1; hasan >= 0; hasan--){
      A = countingSort(A, size, hasan, counter);
    }
    arr = A+1;
    if(!ascending){
        A = reverse(arr,size);
    }
    
    arr = A;
    return counter;    
    
}
