#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double sum, last, control;
int len;

double f(double x, double a, double e) {
    
    sum = 0; len = 1; last = 0;
    last = cos(a) + x*sin(a);
    control = last;
    while (fabs(last) > e) {
        sum += last;
        last = -((x*x*last)/((len*2-1)*len*2));
        len += 1;       
    }
    return sum+last;
}

int main() {
    sum = 0; len = 1; last = 0;
    double x, a, e;
   
    printf("Введите: x, a, e\n");
    if (scanf("%lf %lf %lf", &x, &a, &e) != 3) {
        printf("Ошибка: неверный ввод\n");
        return 1;
    }
    if (e <= 0) {
        printf("Ошибка: точность должна быть > 0\n");
        return 1;
    }
    double res = f(x, a, e);
    printf("Контрольное значение: %.12lf\n", control);
    printf("Точность   Сумма ряда   Последнее слагаемое   Число слагаемых\n");
    printf("%5lf %14.10lf %14.10lf %10d\n", e, res, last, len);
    res = f(x, a, e/10);
    printf("%5lf %14.10lf %14.10lf %10d\n", e/10.0, res, last, len);
    res = f(x, a, e/100);
    printf("%5lf %14.10lf %14.10lf %10d\n", e/100.0, res, last, len);
}