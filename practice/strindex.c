#include <stdio.h>
#include <string.h>

int strindex (char s[100], char t) {
    int n = 0;
    int l = strlen(s);
    for (int i = 0; i < l; i++) {
        if (s[i] == t) {
            n = i + 1;
        }
    }
    if (n) {
        return n;
    }
    return -1;
}

int main () {
    printf("%d", strindex("eefef", 'z'));
}