#include <stdio.h>
#include <float.h>

int main() {

    int n; // длина массива

    printf("Введите количество элементов массива n: "); // запрос длины массива
    if (scanf("%d", &n) != 1 || n < 3) {
        printf("Размер массива должен быть не менее 3");
        return 1;
    }

    double arr[n]; // создание массива

    printf("Введите %d вещественных чисел\n", n); // запрос чисел в массив
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    double min = DBL_MAX;

    for (int i = 0; i < n; i += 2) {  // нахождение минимальных элементов с нечетными номерами
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    double sum = 0; // сумма минимальных элементов с нечетными номерами

    for (int i = 0; i < n; i += 2) { // нахождение sum
        if (arr[i] == min) {
            sum += min;
        }
    }

    double max = -DBL_MAX; // максимальное произведение трех соседних элементов

    for (int i = 0; i < n - 2; i++) { // нахождение max
        double curr = arr[i]*arr[i+1]*arr[i+2];
        if (curr > max) {
            max = curr;
        }
    }

    double prelast = arr[n-2]; // предпоследний элемент
    int new_n = 0; // длина массива из предпоследних элементов

    for (int i = 0; i < n; i++) { // нахождение new_n
        if (arr[i] == prelast) {
            new_n++;
        }
    }

    double new_arr[new_n];

    for (int i = 0; i < new_n; i++) {
        new_arr[i] = prelast;
    }

    printf("Сумма минимальных элементов с нечетными номерами: %.2lf\n", sum);
    printf("Максимальное произведение трех соседних элементов: %.2lf\n", max);
    printf("Новый массив: ");
    for (int i = 0; i < new_n; i++) {
        printf("%.2lf ", new_arr[i]);
    }
    printf("\n");
}