#include <stdio.h>

double C;
int main() {
    for (int i = 300; i >= 0; i -= 20) {
        C = ((double)i - 32) * 5 / 9;
        printf("%d %.1lf\n", i, C);
    }
    return 0;
}