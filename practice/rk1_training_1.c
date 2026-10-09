#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    int l = strlen(str);
    for (int i=0; i<l/2; i++) {
        char tmp=str[i];
        str[i]=str[l-1-i];
        str[l-1-i]=tmp;
    }
}

int main() {
    char str[] = "abcdef";
    reverse_string(str);
    printf("%s\n", str);
}