#include <stdio.h>

void f(int x, int a[]) { x = x + 1; a[0] = a[0] + 1; }

int main() {
    int n = 5, arr[2] = {5, 5};
    f(n, arr);
    printf("%d %d", n, arr[0]);
}