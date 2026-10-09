#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum opType {DIV, ADD, MUL, SUB, MOD, AND, OR, END, NOTHING} opType;
typedef struct Stack_node {
    struct Stack_node* next;
    double value;
    opType type;
} stack;

stack* init_stack() {
    stack* s = (stack*)malloc(sizeof(stack));
    s->opType = END;
}

int is_empty(stack* s) {
    return (s->type==END);
}

void push(stack *s, double val) {
    stack *temp = (stack*)malloc(sizeof(stack));
    temp->value = val;
    temp->next = s;
    s = temp;
}

double pop(stack* s) {
    if (!is_empty(s)) {
        double temp = s->value;
    } else {
        printf("Stack is empty\n");
    }
}

double postfix_notation(const char *x) {
    stack stack;
    init_stack(&stack);

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
                    case '+': push(&stack, b + a); break;
                    case '-': push(&stack, b - a); break;
                    case '*': push(&stack, b * a); break;
                        // case '^': push(&stack, (a, b)); break;
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
    if (!is_empty(&stack)) {
        printf("Incorrect input\n");
        free(input);
    }
    free(input);
    return result;
}
int main () {
    char input[] = "3 4 + 2 * 7 /"; // (((3 + 4)*2)/7)
    printf("%s = ", input);
    double res = postfix_notation(input);
    printf("%.2lf\n", res);
    return 0;
}

