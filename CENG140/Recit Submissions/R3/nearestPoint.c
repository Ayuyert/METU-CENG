#include <stdio.h>
#include <math.h>
/* you can add math library */

int main()
{
	float bir;
	float iki;
	float uc;
	float dort;
	float bes,alti,yedi,sekiz,dokuz,on;
	float kisa;
    int i;
    int yer;
    int k;
    int xcoors[10];
    int ycoors[10];
    int x1, x2,x3,x4,x5,x6,x7,x8,x9,xo,y1,y2,y3,y4,y5,y6,y7,y8,y9,yo,xre,yre;
    
    for (i=0; i<10; i++){
        scanf("%d ", &xcoors[i]);
    }
    
    for (i=0; i<10; i++){
        scanf("%d ", &ycoors[i]);
    }
    scanf("%d",&xre);
    scanf("%d",&yre);
    
    x1=xcoors[0];
    x2=xcoors[1];
    x3=xcoors[2];
    x4=xcoors[3];
    x5=xcoors[4];
    x6=xcoors[5];
    x7=xcoors[6];
    x8=xcoors[7];
    x9=xcoors[8];
    xo=xcoors[9];
    y1=ycoors[0];
    y2=ycoors[1];
    y3=ycoors[2];
    y4=ycoors[3];
    y5=ycoors[4];
    y6=ycoors[5];
    y7=ycoors[6];
    y8=ycoors[7];
    y9=ycoors[8];
    yo=ycoors[9];
    
     
  bir=(xre-x1)*(xre-x1)+(yre-y1)*(yre-y1);
  iki=(xre-x2)*(xre-x2)+(yre-y2)*(yre-y2);
  uc=(xre-x3)*(xre-x3)+(yre-y3)*(yre-y3);
  dort=(xre-x4)*(xre-x4)+(yre-y4)*(yre-y4);
  bes=(xre-x5)*(xre-x5)+(yre-y5)*(yre-y5);
  alti=(xre-x6)*(xre-x6)+(yre-y6)*(yre-y6);
  yedi=(xre-x7)*(xre-x7)+(yre-y7)*(yre-y7);
  sekiz=(xre-x8)*(xre-x8)+(yre-y8)*(yre-y8);
  dokuz=(xre-x9)*(xre-x9)+(yre-y9)*(yre-y9);
  on=(xre-xo)*(xre-xo)+(yre-yo)*(yre-yo);
     
     
    kisa=bir;
    yer=0;
    
    
   if(kisa>iki){
   	
   	kisa=iki;
   	yer=1;
   	
   }
     
    if(kisa>uc){
   	
   	kisa=uc;
   	yer=2;
   	
   }
   
   if(kisa>dort){
   	
   	kisa=dort;
   	yer=3;
   	
   }
   
   if(kisa>bes){
   	
   	kisa=bes;
   	yer=4;
   	
   }
   
   
   if(kisa>alti){
   	
   	kisa=alti;
   	yer=5;
   	
   }
   
   
   if(kisa>yedi){
   	
   	kisa=yedi;
   	yer=6;
   	
   }
   
   
   if(kisa>sekiz){
   	
   	kisa=sekiz;
   	yer=7;
   	
   }
   
   
   if(kisa>dokuz){
   	
   	kisa=dokuz;
   	yer=8;
   	
   }
   
   
   if(kisa>on){
   	
   	kisa=on;
   	yer=9;
   	
   }
   kisa=sqrt(kisa);
   
printf("P = (%d,%d), nearest point index = %d, distance = %.1f",xre,yre,yer,kisa);
     
  
    return 0;
}
