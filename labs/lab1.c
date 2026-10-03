#include <stdio.h> // 1.4
// a1x + b1y = c1
// a2x + b2y = c2
int main() { 
    int a1, b1, c1;
    int a2, b2, c2;
    scanf("%d %d %d\n", &a1, &b1, &c1);
    scanf("%d %d %d\n", &a2, &b2, &c2);
    int del = a1 * b2 - a2 * b1;
    int del1 = c1 * b2 - c2 * b1;
    int del2 = a1 * c2 - a2 * c1;
    if (del == 0 && del1 == 0 && del2 == 0) {
        printf("Бесконечно много решений\nПрямые параллельны\n");
    }
    if (del == 0 && (del1 != 0 || del2 != 0)) {
        printf("Нет решений\nПрямые параллельны\n");
    }
    if (del != 0) {
        printf("Единственное решение\n");
        float x = (float)del1 / del;
        float y = (float)del2 / del;
        if (a1*a2 + b1*b2 == 0) {
            printf("Прямые перпендикулярны\n");
        }
        printf("%.1f %.1f\n", x, y);
    }
    return 0;
}