#include <stdio.h>

void binary(long long num) {
    char bin[100];
    int idx = 0;
    while (num > 0) {
        bin[idx++] = (num % 2) + '0';
        num = num / 2;
    }
    for (int i = idx - 1; i >= 0; i--) {
        printf("%c", bin[i]);
    }
}

int is_prime(long long num) { // проверка числа на простое
    if (num <= 1) return 0;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int check_bin(long long x) { // проверка, что число в двоичной записи чередует 1 и 0
    long long curr_bit;
    long long prev_bit;
    prev_bit = x % 2;
    x = x / 2;
    while (x > 0) {
        curr_bit = x % 2;
        if (curr_bit == prev_bit) return 0;
        prev_bit = curr_bit;
        x = x / 2;
    }
    return 1;
}

int main () { // поиск чисел
    long long n;
    int found = 0;
    printf("Введите натуральное число n: ");
    if (scanf("%lld", &n) != 1) {
        printf("Ошибка ввода");
        return 0;
    }
    printf("Искомые нсатуральные простые числа не превосходящие %lld :\n", n);
    for (long long i = 2; i <= n; i++) {
        if (is_prime(i) && check_bin(i)) {
            printf("Десятичное: %lld | Двоичное: ", i);
            binary(i);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Таких чисел в заданном диапазоне нет\n");
    }
    return 0;
}