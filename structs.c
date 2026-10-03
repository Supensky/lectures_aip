#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
    int l;
    char data[0];
};
char* struct_to_c(struct my_struct* x) { // структура -> C
    char* c = malloc(x->l + 1);
    memcpy(c, x->data, x->l);
    c[x->l] = '\0';
    return c;
}

struct my_struct* struct_from_c(char* c) { // С -> структура
    int len = strlen(c);
    struct my_struct *x = malloc(sizeof(struct my_struct) + len);
    x->l = len;
    memcpy(x->data, c, len);
    return x;
}

struct my_struct* struct_sum(struct my_struct* x, struct my_struct* y) { // Сложение
    int new_l = x->l + y->l;
    struct my_struct* res = malloc(sizeof(struct my_struct) + new_l + 1);
    res->l = new_l;
    memcpy(res->data, x->data, x->l);
    memcpy(res->data + x->l, y->data, y->l);
    return res;
}

int struct_comp(struct my_struct* x, struct my_struct* y) { // Сравнение
    int min_l = (x->l < y->l) ? x->l : y->l;
    int cmp = memcmp(x->data, y->data, min_l);
    if (cmp) return cmp;
    if (x->l < y->l) return -1;
    if (x->l > y->l) return 1;
    return 0;
}

int main() {
    char* c_str = struct_to_c(struct_from_c("Hello"));
    printf("c_str = %s\n", c_str);

    struct my_struct* x = struct_from_c("Hello");
    printf("x = %s\n", struct_to_c(x));

    free(c_str);
    free(x);
}