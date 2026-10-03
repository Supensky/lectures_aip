#include <stdio.h>
#define STRINGIFY(x) #x 


#define STR(x) #x 
#define CONCAT(a, b) a##b 
int main() {
    printf("%s\n", STRINGIFY(2+3*4));

    
    printf("%s\n", STR(hello));
    int CONCAT(var, 123) = 5;
    return 0;
}
