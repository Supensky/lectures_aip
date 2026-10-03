#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(){
    char foo[]="906";

printf("Length: %lu\n", strlen(foo));
char* ptr = foo;
do {
    printf("0x%x %c\n", *ptr, *ptr);
    ++ptr;
} while (*ptr != '\0'); }