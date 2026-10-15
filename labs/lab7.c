#include <stdio.h>
#include <stdlib.h>

int n;
int **input_array() {
    printf("Введите размер n для массива n x n: ");
    scanf("%d", &n);
    printf("Введите %d элементов матрицы (0 и 1): ", n * n);
    int **arr = (int **)malloc(n * sizeof(int)); // указатель на указатель
    for (int i = 0; i < n; i++) {
        arr[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    return arr;
}

void swap_90(int **arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int temp = arr[i][j];
            arr[i][j] = arr[n - 1 - j][i];
            arr[n - 1 - j][i] = temp;
        }
    }
}

void print_array(int **arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int **arr = input_array();
    print_array(arr, n, n);
    swap_90(arr, n, n);
    print_array(arr, n, n);
    free(arr);
    return 0;
}


