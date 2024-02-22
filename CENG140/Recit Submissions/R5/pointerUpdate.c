#include <stdio.h>
#include "pointerUpdate.h"

void update(int * arr[], int length){
    int i;
    int k[200000];
    int a;
    
    for(i=0;i<length;i++){
        k[i]=*arr[i];}
  for(i=0;i<length;i++){
     
      a=*arr[i]%length;
      *arr[i]=k[a];
  
   
  }
}
