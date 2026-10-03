#include <stdio.h>

// Функция для обмена мест двух элементов
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Функция быстрой сортировки
void quicksort(int arr[], int low, int high) {
    int i = low;
    int j = high;

    // Выбираем опорный элемент (pivot) в самом центре
    int pivot = arr[(low + high) / 2];

    // Делим массив на две части
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Рекурсивные вызовы для левой и правой частей
    if (low < j) {
        quicksort(arr, low, j);
    }
    if (i < high) {
        quicksort(arr, i, high);
    }
}

// Функция для печати массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sort: \n");
    printArray(arr, n);

    quicksort(arr, 0, n - 1);

    printf("After sort: \n");
    printArray(arr, n);

    return 0;
}
