#include <stdio.h>
/* Celsius-Fahrenheit table*/
int main()
{
printf("Celsius\t\tFahrenheit\n");
float fahr, celsius;
float lower, upper, step;
lower = 0;
upper = 300;
step = 20;
celsius = lower;
while (celsius <= upper) 
{
  fahr = (9.0*celsius)/5.0 +32.0;
  printf("%3.0f\t\t%6.1f\n", celsius,fahr);
  celsius = celsius + step;
}
}
