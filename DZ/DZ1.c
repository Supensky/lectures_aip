#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {               // стек
    double data[100];          // data[размер стека]
    int top;                   // переменная, хранящая индекс самого верхнего элемента в массиве
} Stack;

void initStack(Stack *s) {                        // инициализация стека
    s->top = -1;
}

int isEmpty(Stack *s) {                           // проверка пуст ли стек в данный момент
    return s->top == -1;                          // 1 - пуст, 0 - не пуст
}

void push(Stack *s, double val) {                 // операция добавления нового числа на верх стека
    if (s->top < 99) {                            // есть ли свободное место в стеке
        s->data[++(s->top)] = val;                // увеличиваем top на 1 и кладем число на верх стека
    } else {
        printf("Stack is full\n");          // ошибка, места в стеке нет
    }
}

double pop(Stack *s) {                      // возвращает самое верхнее число из стека, удаляя его оттуда
    if (!isEmpty(s)) {                            // если число есть в стеке
        return s->data[s->top--];                 // Возвращаем верхнее число, уменьшаем top на 1
    } else {
        printf("Stack is empty\n");         // ошибка, стек пуст
    }
}

double postfix_notation(const char *x) {
    Stack stack;                                  // создание переменной для хранения стека
    initStack(&stack);                            // инициализация стека

    char *input = strdup(x);                      // копируем все символы исходной строки
    char *token = strtok(input, " ");        // разбиение по пробелам

    while (token != NULL) {                       // пока в строке есть элементы
        char *endptr;                             // указатель на символ
        double val = strtod(token, &endptr);      // из str в double, если число

        if (endptr != token && *endptr == '\0') { // если было распознано число
            push(&stack, val);                    // добавляем элемент в вершину стека
        } else {                                  // если не число, значит это оператор
            if (strlen(token) == 1) {             // проверяем что в token лежит один символ
                double b = pop(&stack);           // число b
                double a = pop(&stack);           // число a
                switch (token[0]) {
                    case '+': push(&stack, a + b); break; // a + b
                    case '-': push(&stack, a - b); break; // a - b
                    case '*': push(&stack, a * b); break; // a * b
                    case '/':
                        if (b == 0) { // знаменатель не равен 0
                            printf("Division by zero\n"); // ошибка, деление на 0
                            free(input); // освобождение памяти
                            return 0.0;
                        }
                    push(&stack, a / b); break; // a / b
                    default:                       // если не был распознан ни один из операторов
                        printf("Unknown operator\n"); // ошибка, неизвестный оператор
                        free(input);                        // освобождение памяти
                        return 0.0;
                }
            }
        }
        token = strtok(NULL, " ");           // переход к следующему числу/знаку
    }
    double result = pop(&stack);                  // забираем result из стека
    if (!isEmpty(&stack)) {                       // если стек пуст
        printf("Некорректное выражение ОПЗ\n"); // ошибка
        free(input);                              // освобождаем память
    }
    free(input);                                  // освобождаем память
    return result;                                // возвращаем result
}

int main () {
    char input[] = "3 4 + 2 * 7 /"; // (((3 + 4)*2)/7)
    printf("%s = ", input);
    double res = postfix_notation(input);
    printf("%.2lf\n", res);
    return 0;
}