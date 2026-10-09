#include <stdio.h>
#include <stdlib.h>

int *get_vector() {
    // массив уничтожается при выходе из функции, поэтому используем static чтобы обозначить
    int *arr = malloc(sizeof(int) * 3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    return arr;
}
int main() {
    int *ptr = get_vector();
    for (int i = 0; i < 3; i++) {
        // <= заменено на < так как i = 0,1,2,3 выйдет за рамки массива
        printf("%d ", ptr[i]);
    }
    free(ptr);
    return 0;
}
