#include <stdio.h>
#include "recit_4_2.h"
#define ERROR 0.000001
#define PI 3.1415926

int carpim=1;
float bolum=0;
int k=0;
int n=0;
double app=0;
int sayi;
int sayac=0;
float d;

int sayacsayar(tek){
    
    return tek++;
}


int combinations(int n,int k){
    carpim =1;
    if (k>(n/2)){
        printf("(%d %d)\n",n,k);
        
        k=n-k;
        
    }
    
    
	
	if (k==0){
	   printf("(%d %d)\n",n,k);
	   
	    return 1;
		
	}
    bolum=(float)n/k;
    printf("(%d %d)\n",n,k);
    
    carpim=carpim*bolum * combinations (--n,--k);
    
	return carpim;
	 
	
	
    
}






double sine(double x, int iter){
    
    d=(float)power(-1,sayac)*power(x,(2*sayac+1))/factorial(2*sayac+1);
    absolute(d);
    if (iter==0 || d <ERROR){
        sayac=0;
        return 0;
    }
    
    iter --;
    printf("%d",iter);
    
    app+=(float)power(-1,sayac)*power(x,(2*sayac+1))/factorial(2*sayac+1);
    printf("sin(%f) = %f at recursive call %d\n",x,d,sayac+1);
    sayac++;
    
    return app;

}
