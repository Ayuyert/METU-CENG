#include <stdio.h>

int main(){
	
	int wall[2000000]={0};
	int t=0;
	int i;	
	int j;
	int k;
	int len;
	int num_trib;
	int width;
	int height_trib;
	int time;
	int pos;
	int speed;
	int interval;
	int atk_num;
	
	scanf(" %d",&len);
	for (i=0;i<=len;i++){
		
		wall[i]=1;
	}
	scanf(" %d",&num_trib);
	 
	for (i=0;i<num_trib;i++){
		
		scanf(" %d",&width);
		scanf(" %d",&height_trib);
		scanf(" %d",&time);
		scanf(" %d",&pos);
		scanf(" %d",&speed);
		scanf(" %d",&interval);
		scanf(" %d",&atk_num);
		
			for (j=0;j<atk_num;j++){
				
				if(pos+width<0 || pos>100000 ||pos>len){
				pos += interval*speed;
				
				continue;}
				
				if(pos+width>0 && pos<0){
				
					
					width=pos+width;
					pos=0;
					
					
				}
				if(pos <100000 && pos+width>100000){
				
					width=100000-pos-1;
					
				}
				
				for (k=0;k<width;k++){
					
					if (wall[pos+k]<height_trib){
						
						wall[pos+k]=height_trib;	
						
					}
					
				}
				pos+=interval*speed;
				
				
				
				
				
			}
		
			
	}
	

	
	while(t<len){

	printf("%d ",wall[t]);
	t++;
}
    printf("%d",wall[t]);
	
	printf("\n");
	
	return 0;
}
