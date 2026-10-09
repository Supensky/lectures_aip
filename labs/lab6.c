#include <stdio.h>
#include <stdlib.h>


int n;
int k;
double *input_array() {
    printf("Введите длину массива n: ");
    scanf("%d", &n);
    double *arr = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &arr[i]) != 1) {
            printf("Ошибка! Введите вещественное число.");
        }
    }
    return arr;
}

void print_array(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2lf\n", arr[i]);
    }
}

void remove_element(double *arr, int n, int index) {
    if (index >= 0 && index < n) {
        for (int i = index; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
    }
}

void del_negative(double *arr, int n) {
    k = 0;
    for (int i = n-1; i >= 0; i--) {
        if (arr[i] < 0) {
            remove_element(arr, n, i);
            k += 1;
        }
    }
    k = n - k;
    arr = (double *)realloc(arr, sizeof(double) * k);
}

void mas_sort(double *arr, int n) {
    int i,bb=1;
    double buf;
    i = n - 1;
    while (bb) {
        bb = 0;
        for (int j = 0; j < i; j++) {
            if ((arr[j]) > (arr[j + 1])) {
                buf = arr[j];
                (arr[j]) = (arr[j + 1]);
                (arr[j + 1]) = buf;
                bb = 1;
            }
        }
        i--;
    }
}

int main() {
    double *arr = input_array();
    mas_sort(arr, n);
    del_negative(arr, n);
    print_array(arr, k);
    free(arr);
    return 0;
}