#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100

// Простая структура стека для хранения чисел типа double
typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, double val) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = val;
    } else {
        printf("Ошибка: стек переполнен\n");
        exit(EXIT_FAILURE);
    }
}

double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    } else {
        printf("Ошибка: стек пуст\n");
        exit(EXIT_FAILURE);
    }
}

// Функция вычисления ОПЗ из строки
double evaluateRPN(const char *expr) {
    Stack stack;
    initStack(&stack);

    // Копия строки для токенизации с помощью strtok
    char *input = strdup(expr);
    char *token = strtok(input, " ");

    while (token != NULL) {
        // Проверяем, является ли токен числом
        char *endptr;
        double num = strtod(token, &endptr);

        // Если strtod смогла распознать число
        if (endptr != token && *endptr == '\0') {
            push(&stack, num);
        } else {
            // Иначе это оператор
            if (strlen(token) == 1) {
                double b = pop(&stack);
                double a = pop(&stack);
                switch (token[0]) {
                    case '+': push(&stack, a + b); break;
                    case '-': push(&stack, a - b); break;
                    case '*': push(&stack, a * b); break;
                    case '/':
                        if (b == 0) {
                            printf("Ошибка: деление на ноль\n");
                            free(input);
                            exit(EXIT_FAILURE);
                        }
                        push(&stack, a / b);
                        break;
                    default:
                        printf("Ошибка: неизвестный оператор %s\n", token);
                        free(input);
                        exit(EXIT_FAILURE);
                }
            }
        }
        token = strtok(NULL, " ");
    }

    double result = pop(&stack);
    if (!isEmpty(&stack)) {
        printf("Ошибка: некорректное выражение ОПЗ\n");
        free(input);
        exit(EXIT_FAILURE);
    }

    free(input);
    return result;
}

int main() {
    // Пример: (3 + 4) * 2 -> в ОПЗ: "3 4 + 2 *"
    char expression[] = "3 4 + 2 *";
    printf("Выражение ОПЗ: %s\n", expression);
    double res = evaluateRPN(expression);
    printf("Результат: %.2f\n", res);
    return 0;
}
