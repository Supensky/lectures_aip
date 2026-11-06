#include <stdio.h>

int f(char *mas) {
    int sum = 0;
    int i = 1;
    for (; mas[i]; ++i) {
        if (mas[i] >= '0' && mas[i] <= '9' && mas[i]==mas[i-1]) {
            sum += mas[i] - '0';
        }
    }
    if (mas[i-1] == mas[0]) {
        sum += (mas[i-1] - '0');
    }
    return sum;
}

int main() {
    char mas[100]="0";
    int cnt = 0;
    while (scanf("%s", mas) != -1){
        cnt += f(mas);
        break;
    }
    printf("%d first \n", cnt);
    return 0;
}
// сумму всех цифр что следующая за ней совпадает