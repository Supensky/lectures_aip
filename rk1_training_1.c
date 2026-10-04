#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int l = strlen(str);
    for (int i = l - 1; i >= 0; i--) {
        printf("%c", str[i]);
    }
}

int main() {
    char str[] = "abcdef";
    reverse_string(str);
}