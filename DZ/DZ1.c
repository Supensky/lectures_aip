#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Stack {
    double value;
    struct Stack* next;
} stack;

stack* init_stack(double value) {
    stack* s = (stack*)malloc(sizeof(stack));
    if (s == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    s -> value = value;
    s -> next = NULL;
    return s;
}

int is_empty(stack* s) {
    return s == NULL;
}

void push(stack **head, double val) {
    stack *newstack = init_stack(val);
    newstack -> next = *head;
    *head = newstack;
}

double pop(stack **head) {
    if (!is_empty(*head)) {
        stack *temp = *head;
        double val = temp -> value;
        *head = (*head) -> next;
        free(temp);
        return val;
    } else {
        // Изменено: не пишем здесь ошибку в stdout,
        // так как логику нехватки операндов лучше обрабатывать в самой функции калькулятора
        return 0.0;
    }
}

double postfix_notation(const char *x) {
    stack *head = NULL;

    char *input = strdup(x);
    char *token = strtok(input, " ");

    while (token != NULL) {
        char *endptr;
        double val = strtod(token, &endptr);

        if (endptr != token && *endptr == '\0') {
            push(&head, val);
        } else {
            // Проверяем, что это действительно один из известных односимвольных операторов
            if (strlen(token) == 1 && strchr("+-*/^", token[0]) != NULL) {

                // Валидация: для бинарной операции нужно минимум 2 элемента в стеке
                if (is_empty(head) || is_empty(head->next)) {
                    printf("Error: Not enough operands for operator '%c'\n", token[0]);
                    free(input);
                    // Очистка стека перед выходом
                    while(!is_empty(head)) pop(&head);
                    return 0.0;
                }

                double b = pop(&head);
                double a = pop(&head);

                switch (token[0]) {
                    case '+': push(&head, a + b); break;
                    case '-': push(&head, a - b); break;
                    case '*': push(&head, a * b); break;
                    case '^': push(&head, pow(a, b)); break;
                    case '/':
                        if (b == 0.0) {
                            printf("Error: Division by zero\n");
                            free(input);
                            while(!is_empty(head)) pop(&head);
                            return 0.0;
                        }
                        push(&head, a / b); // ИСПРАВЛЕНО: Добавлен недостающий оператор
                        break;
                }
            } else {
                printf("Unknown token or operator: %s\n", token);
                free(input);
                while(!is_empty(head)) pop(&head);
                return 0.0;
            }
        }
        token = strtok(NULL, " ");
    }

    if (is_empty(head)) {
        printf("Error: Empty expression\n");
        free(input);
        return 0.0;
    }

    double result = pop(&head);

    if (!is_empty(head)) {
        printf("Incorrect input (too many operands)\n");
        while (!is_empty(head)) {
            pop(&head);
        }
    }

    free(input);
    return result;
}

int main () {
    char input[] = "3 4 + 2 * 7 /"; // (((3 + 4)*2)/7) = 14 / 7 = 2.00
    printf("%s = ", input);
    double res = postfix_notation(input);
    printf("%.2lf\n", res);
    return 0;
}
