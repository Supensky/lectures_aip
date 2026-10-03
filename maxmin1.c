#include <stdio.h>
#include <limits.h>

// Функция принимает целую строку, ищет в ней max и min, и возвращает их разность
int f(char *mas) {
    char *ptr = mas;
    int num;
    int offset;
    
    int min = INT_MAX;
    int max = INT_MIN;
    int count = 0;

    // Разбираем строку по числам с помощью sscanf
    while (sscanf(ptr, "%d%n", &num, &offset) == 1) {
        if (num > max) max = num;
        if (num < min) min = num;
        count++;
        
        ptr += offset; // Сдвигаем указатель на длину прочитанного числа
    }

    // Если в строке были числа, возвращаем разность, иначе 0
    return (count > 0) ? (max - min) : 0;
}

int main() {
    char mas[1000];
    int sum = 0;

    // Читаем поток ПОСТРОЧНО. Каждая строчка обрабатывается отдельно
    while (fgets(mas, sizeof(mas), stdin) != NULL) {
        sum += f(mas);
    }

    printf("Сумма разностей: %d\n", sum);
    return 0;
}
