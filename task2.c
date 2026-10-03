#include <stdio.h>

double my_fabs(double x) { return x < 0 ? -x : x; }

double my_floor(double x)
{
    long long i = (long long)x;
    if (x < 0 && x != (double)i) i -= 1;
    return (double)i;
}

double func(double x)
{
    /* приводим x к [0, 5) — период 5 */
    x -= my_floor(x / 5.0) * 5.0;

    if (x < 2) return my_fabs(x - 1);
    if (x < 3) return my_fabs(x - 3);
    return x - 3;
}

int main(void)
{
    double a, b;
    int n;

    if (scanf("%lf %lf %d", &a, &b, &n) != 3 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    double step = (b - a) / n;
    double min = func(a), max = func(a);

    printf("index \t x\t\t y\t\t min\t\t max\n");
    for (int i = 0; i <= n; i++) {
        double x   = a + step * i;
        double res = func(x);
        if (res < min) min = res;
        if (res > max) max = res;
        printf("%d \t%7.4lf \t%7.4lf \t%7.4lf \t%7.4lf\n",
               i, x, res, min, max);
    }
    return 0;
}