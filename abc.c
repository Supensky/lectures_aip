#include <stdio.h>
#include <ctype.h>

int main() {
//    char line[100] = "Hello, world";
    char line[100];
    int b = 0;
    int mas[26] = {}; // массив из 26 нулей
    fgets(line, 100, stdin);
//    for (int i = 0; i < 26; i++) mas[i] = 0; // memset, bzero,
    for (int i = 0; i < 100; i++) {
        if (isalpha(line[i])) {
            mas[tolower(line[i]) - 'a'] += 1;
            b++;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (mas[i] != 0) printf("%c  %.0f %c\n", i+'a', ((float)mas[i]/b)*100,'%');
    }
}