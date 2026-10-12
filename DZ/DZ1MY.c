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
        printf("Stack is empty\n");
        return -1.0;
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
            if (strlen(token) == 1) {
                double b = pop(&head);
                double a = pop(&head);
                switch (token[0]) {
                    case '+': push(&head, a + b); break;
                    case '-': push(&head, a - b); break;
                    case '*': push(&head, a * b); break;
                    case '^': push(&head, pow(a, b)); break;
                    default:
                        printf("Unknown operator\n");
                        free(input);
                        return 0.0;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    double result = pop(&head);
    if (!is_empty(head)) {
        printf("Incorrect input\n");
        free(input);
    }
    free(input);
    return result;
}
int main () {
    char input[] = "3 4 + 2 * 7 - 2 ^"; // (((3 + 4)*2)-7)^2
    printf("%s = ", input);
    double res = postfix_notation(input);
    printf("%.2lf\n", res);
    return 0;
}