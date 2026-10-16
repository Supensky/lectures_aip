#include <stdio.h>
#include <stdlib.h>

int n;
int **input_array() { // функция ввода массива
    printf("Введите размер n для массива n x n: ");
    scanf("%d", &n);
    printf("Введите %d элементов матрицы (0 и 1): ", n * n);
    int **arr = (int **)malloc(n * sizeof(int *)); // указатель на указатель
    for (int i = 0; i < n; i++) {
        arr[i] = (int *)malloc(n * sizeof(int)); // динамическое выделение памяти для массива
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]); // заполнение массива элементами
        }
    }
    return arr;
}

void rotate_90(int **arr, int n, int m) { // функция поворота на 90 градусов против часовой стрелки
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            int temp = arr[i][j];
            arr[i][j] = arr[j][n - i - 1];
            arr[j][n - 1 - i] = arr[n - 1 - i][n - 1 - j]; // перестановка элементов
            arr[n - 1 - i][n - 1 - j] = arr[n - 1 - j][i];
            arr[n - 1 - j][i] = temp;
        }
    }
}

void free_array(int **arr, int size) { // построчное освобождение массива
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

void print_array(int **arr, int n, int m) { // вывод массива на экран
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int **arr = input_array(); // ввод массива
    print_array(arr, n, n); // вывод исходного массива
    rotate_90(arr, n, n); // обработка исходного массива
    print_array(arr, n, n); // вывод обработанного массива
    free_array(arr, n); // освобождение памяти
    return 0;
}