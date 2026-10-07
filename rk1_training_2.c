#include <stdio.h>
#include <stdlib.h>

int main() {
    int len = 2, l = 0, a, *arr;
    arr = (int *)malloc(sizeof(int) * len);
    while (1) {
        scanf("%d", &a);
        if (a == 0) {
            break;
        }
        if (l == len) {
            len *= 2;
            arr = (int *)realloc(arr, sizeof(int) * len);
        }
        arr[l] = a;
        l++;
    }
    for (int i = l-1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
