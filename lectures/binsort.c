#include <stdio.h>

// Функция бинарного поиска для определения позиции вставки
int binarySearch(int arr[], int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}

// Функция бинарной сортировки вставками
void binaryInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;

        // Находим позицию для вставки элемента arr[i]
        int loc = binarySearch(arr, temp, 0, j);

        // Сдвигаем элементы вправо, чтобы освободить место
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int main() {
    int arr[] = {37, 23, 0, 17, 12, 72, 31};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sort:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    binaryInsertionSort(arr, n);

    printf("After sort:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

