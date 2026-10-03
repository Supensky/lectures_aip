#include <stdio.h>

float f(float x) { // принимает аргумент функции и возвращает ее значение
    if (x >= 4 || x < 0) x -= ((int)x / 4) * 4;
    if (x < 0) x += 4;
    if (0 <= x && x < 1) return x;
    if (1 <= x && x < 3) return -x + 2;
    if (3 <= x && x < 4) return x - 4;
}
int main() { // выводит на экран номер и значение точки табулирования, соответствующие им значения, min и max
    float a, b;
    int n;
    scanf("%f %f %d", &a, &b, &n);  // чтение параметров
    float min = f(a);
    float max = f(a);
    printf("i\t x\t y\t min\t max\n"); // вывод шапки
    for (int i = 0; i < n; i++) {
        float x = a + (b-a) / n * i;
        float y = f(x);
        if (y < min) min = y;
        if (y > max) max = y;
        printf("%d\t%5.2f \t%5.2f \t%5.2f \t%5.2f\n", i + 1, x, y, min, max); // вывод по точка табулирования
    }
    printf("min: %.2f max: %.2f\n", min, max); // вывод максимального и минимального значения на диапазоне
    return 0;
}