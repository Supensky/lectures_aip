#include <stdio.h>
#include <string.h>

int f(char *mas) {
    int n = strlen(mas);
    int min = (mas[0] - '0');
    int max = (mas[0] - '0');
    for (int i = 0; i < n; i++) {
        if (mas[i] == ' ') continue;
        int  num = mas[i] - '0';
        if (num > max) {
            max = mas[i] - '0';
        }
        if (num < min) {
            min = mas[i] - '0';
        }
    }
    int del = max - min;
    return del;
}

int main() {
    char mas[1000] = "0";
    int sum = 0;
//    fgets(mas, 100, stdin);
//    sscanf(mas, "%d", int);
    while (scanf("%s", mas) != -1) {sum += f(mas);}
    printf("%d\n", sum);
    return 0;
}