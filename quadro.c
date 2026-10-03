#include <stdio.h>

float fun(float a, float b)
{ float s;
s = a*a + b*b;
return s; }
void main()
{ float x, y, rez;
x=5; y=10;
rez=fun(x, y); /* x, y замещают a,b */
printf("Результат= %7.2f\n",rez); }