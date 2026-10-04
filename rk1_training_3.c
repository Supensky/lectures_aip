#include <stdio.h>

int* get_vector() {
    // массив уничтожается при выходе из функции, поэтому используем static чтобы обозначить
    static int arr[3] = {10, 20, 30}; // глобальную статическую переменную
    return arr;
}

int main() {
    int *ptr = get_vector();
    for (int i = 0; i < 3; i++) { // <= заменено на < так как i = 0,1,2,3 выйдет за рамки массива
        printf("%d ", ptr[i]);
    }
    return 0;
}