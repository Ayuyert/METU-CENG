int main(){

int pzt;
int sali;
int car;
int per;
int cuma;

float a;
float b;
float c;
float d;
float e;
float avg;

scanf("%d %d %d %d %d", &pzt, &sali, &car, &per, &cuma);



a=(pzt-32)/1.8;
b=(sali-32)/1.8;
c=(car-32)/1.8;
d=(per-32)/1.8;
e=(cuma-32)/1.8;

avg=(a+b+c+d+e)/5;

printf("Celsius on Mon: %.2f\n",a);
printf("Celsius on Tue: %.2f\n",b);
printf("Celsius on Wed: %.2f\n",c);
printf("Celsius on Thu: %.2f\n",d);
printf("Celsius on Fri: %.2f\n",e);
printf("Average: %.2f\n",avg);
	
	return 0;
}
