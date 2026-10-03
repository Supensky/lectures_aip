#include <stdio.h>
#include <locale.h> // Обязательный заголовочный файл

int main() {
    setlocale(LC_ALL, ".UTF8"); // Подключение русской локали
    
    printf("Привет, мир!\n");
    
    return 0;
}
