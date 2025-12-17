#include<stdio.h>
/*Fahrenheit to Celsius*/ 
double cel(int fahr)
{
 return ((5.0/9.0) * (fahr-32.0));
}
int main()
{
printf("Fahrenheit\tCelsius\n");
for(int i=0;i<300;i+=20)
{
printf("%3d\t\t%6.1f\n",i,cel(i));
}
return 0;
}
