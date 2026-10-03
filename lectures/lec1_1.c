#include <stdio.h>
#include <stdlib.h>

void map(
    const void *src,
    void *dst,
    size_t num,
    size_t elem_size,
    void (*fn)(const void *in, void *out) // *
) {
    const char *s = src;
    char *d = dst;
    while (num--) {
        fn(s, d);
        s += elem_size;
        d += elem_size;
    }
}

void two_times(const void *in, void *out) {
    int x = *(const int*)in;
    *(int*)out = x * 2;
}

int main() {
    int src[] = {0, 1, 2, 3, 4, 5, 6};
    int dst[6];
    size_t count = sizeof(src) / sizeof(src[0]);
    map(src, dst, count, sizeof(int), two_times);

    for (size_t i = 0; i < count; i++){
        printf("%d", dst[i]);     // выведет 0 2 4 6 8 10
    }
    printf("\n");
    return 0;
}