#include <stdio.h>

int main(){
	
	
	char a;
	int b;
	int c;
	int d;
	
	
	scanf("%c %d %d %d", &a, &b, &c, &d);
	
	
	
	
		if(a == 'E' && b<d-1)
	{
	
		b++;

	
	}else if (a=='W' && b>0){
		
		b--;
		
	}
	
	else if (a=='S' && c<d-1){
		
				
		c++;
	}
	
		else if (a=='N' && c >0){
		
		c--;
	}


	
	
	printf("%d %d", b ,c);
	

	
	return 0;
}
