#include <stdio.h> // метод Крамера
// a1x + b1y = c1
// a2x + b2y = c2
int main() { 
    float a1, b1, c1;
    float a2, b2, c2;
    scanf("%f %f %f\n", &a1, &b1, &c1);  // чтение параметров
    scanf("%f %f %f\n", &a2, &b2, &c2);
    float del = a1 * b2 - a2 * b1; 
    float del1 = c1 * b2 - c2 * b1; // расчет определителей
    float del2 = a1 * c2 - a2 * c1;
    if (del == 0 && del1 == 0 && del2 == 0) { // условие на совпадение
        printf("Бесконечно много решений\nПрямые параллельны\n");
    }
    if (del == 0 && (del1 != 0 || del2 != 0)) { // условие на параллельность
        printf("Нет решений\nПрямые параллельны\n");
    }
    if (del != 0) { // условие на единственное решение
        printf("Единственное решение\n");
        float x = (float)del1 / del;
        float y = (float)del2 / del;
        if (a1*a2 + b1*b2 == 0) { // условие на перпендикулярность
            printf("Прямые перпендикулярны\n");
        }
        printf("%.1f %.1f\n", x, y); // вывод решения
    }
    return 0;
}