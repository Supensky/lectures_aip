#include <stdio.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

int main() {
    printf("%c\n", lower('A'));
    printf("%c\n", lower('z'));
    printf("%c\n", lower('5'));
}