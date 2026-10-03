#include <stdio.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ".UTF8");
    printf("Введите целое число: ");
    int n = 0;
    scanf("%d", &n);
    printf("Число является ");
    if (n % 2 == 0) {
        printf("четным");
    } else {
        printf("нечетным");
    }
    return 0;
}