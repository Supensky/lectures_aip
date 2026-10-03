#include <stdio.h>

int main() {
    // char buf[80] = "1122"; buf[0] = '1' bud[1] = '1' buf[4] = '0'
    
    char x = '5'; // - <= char x <= 127, signed char 128 <= x <= 255
    int n = x -'0'; // перевод символа в число
    printf("%d \n", n);

    char buf[80];
    while (scanf("%s", buf)-'0') { // scanf читает массив в buf
        printf("%c", buf);
    }

    return 0;
}
// сумму всех цифр что следующая за ней совпадает