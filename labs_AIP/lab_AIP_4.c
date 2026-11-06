// 1 развернуть всю строчку
// 2 развернуть каждое слово по отдельности

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    int l = strlen(str);
    for (int i=0; i<l/2; i++) {
        char tmp=str[i];
        str[i]=str[l-1-i];
        str[l-1-i]=tmp;
    }
}

void reverse_word(char *start, char *end) {
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

void reverse_each_word(char *str) {
    int start = 0;
    for (int i=0; i<=strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\0' || str[i] == '\t' || str[i] == '\n') {
            reverse_word(str+start, i-1 + str);
            start = i+1;
        }
    }
}

char* read_file(FILE *f) {
    size_t capacity = 2;
    size_t len = 0;

    char *d_str = (char *)malloc(capacity * sizeof(char));
    int ch;
    while ((ch = fgetc(f)) != EOF && ch != '\n') {
        if (len+1 >= capacity) {
            capacity *= 2;
            char *new_str = (char *)realloc(d_str, capacity * sizeof(char));
            d_str = new_str;
        }
        d_str[len++] = (char)ch;
    }
    d_str[len] = '\0';
    return d_str;
}

void print_string(char *str) {
    for (int i=0; i<strlen(str); i++) {
        printf("%c", str[i]);
    }
}

void file_write(char *str) {
    FILE *f = fopen("output.txt", "w");
    fputs(str, f);
    fclose(f);
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Error opening file");
        return 1;
    }
    char *str = read_file(f);
    fclose(f);
    print_string(str);

    printf("\n");

    reverse_string(str);
    print_string(str);

    printf("\n");

    reverse_each_word(str);
    print_string(str);

    printf("\n");

    file_write(str);
    free(str);
}