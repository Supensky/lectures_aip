#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, double val) {
    if (s-> top < MAX_SIZE) {
        s->data[++(s->top)] = val;
    } else {
        printf("Stack is full\n");
    }
}

double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    } else {
        printf("Stack is empty\n");
    }
}

double postfix_notation(const char *x) {
    Stack stack;
    initStack(&stack);

    char *input = strdup(x);
    char *token = strtok(input, " ");

    while (token != NULL) {
        char *endptr;
        double val = strtod(token, &endptr);

        if (endptr != token && *endptr == '\0') {
            push(&stack, val);
        } else {
            if (strlen(token) == 1) {
                double b = pop(&stack);
                double a = pop(&stack);
                switch (token[0]) {
                    case '+': push(&stack, a + b); break;
                    case '-': push(&stack, a - b); break;
                    case '*': push(&stack, a * b); break;
                    case '^': push(&stack, pow(a, b)); break;
                    default:
                        printf("Unknown operator\n");
                        free(input);
                        return 0.0;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    double result = pop(&stack);
    if (!isEmpty(&stack)) {
        printf("Incorrect input\n");
        free(input);
        return result;
    }
}

int main () {
        char input[] = "3 4 + 2 * 12 - 2 ^";
        printf("%s = ", input);
        double res = postfix_notation(input);
        printf("%.2lf\n", res);
        return 0;
    }
