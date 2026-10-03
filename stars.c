#include <stdio.h>
#include <string.h>

int main() {
    char u = '+', h = '-', v = '|';
    char line[100];
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';
    int len = strlen(line);
    printf("+");
    for (int i = 0; i < len; i++) {
        printf("-");
    }
    printf("+\n|%s|\n+", line);
    for (int i = 0; i < len; i++) {
        printf("-");
    }
    printf("+\n");
    return 0;
}