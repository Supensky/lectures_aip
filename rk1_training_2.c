#include <stdio.h>
#include <stdlib.h>

int main() {
    int k = 2;
    int *arr = (int *)malloc(sizeof(int) * k);
    int a;
    int l = 0;
    while (1) {
        if (scanf("%d", &a) != 1) {
            continue;
        }
        if (a == 0) {
            break;
        }
        if (l == k) {
            k *= 2;
            int *p = (int *)realloc(arr, sizeof(int) * k);
            arr = p;
        }
        arr[l] = a;
        l++;
    }
    for (int i = l-1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    arr = NULL;
    return 0;
}
