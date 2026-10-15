#include <string.h>
#include <stdio.h>


int sign(int num) {
    return 2*(num >> 31) - !num + 1;
}
int main() {
    printf("%d %d %d \n", sign(-5), sign(0), sign(5));
    return 0;
}
