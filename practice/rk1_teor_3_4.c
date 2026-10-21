#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int low = 0;
    int high = n - 1;
    int mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        if (x <= v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return (v[low] == x) ? low : -1;
}

int main() {
    int v[] = {1, 3, 5, 7, 9, 11};
    printf("%d\n", binsearch(7, v, 6));
    printf("%d\n", binsearch(4, v, 6));
    return 0;
}