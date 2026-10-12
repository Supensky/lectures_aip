#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Stack {
    double value;
    char type;
    struct Stack *next;
} stack;

stack* init_stack(double value, char type) {
    stack* s = (stack*)malloc(sizeof(stack));
    s -> value = value;
    s -> next = NULL;
    s->type =type;
    return s;
}

int is_empty(stack* s) {
    return s == NULL;
}

double pop_num(stack **head) {
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

char pop_type(stack **head) {
    if (!is_empty(*head)) {
        stack *temp = *head;
        double val = temp -> type;
        *head = (*head) -> next;
        free(temp);
        return val;
    } else {
        printf("Stack is empty\n");
    }
}

int is_type(stack **head) {
    if (!is_empty(*head)) {
        stack *temp = *head;
        if (temp -> type == 'n') {
            free(temp);
            return 0;
        } else {
            free(temp);
            return 1;
        }
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}

void push(stack **head, double val, char type) {
    stack *newstack = init_stack(val, type);
    newstack -> next = *head;
    *head = newstack;
}

int priority(char c) {
    switch (c){
        case '+': return 0;
        case '-': return 0;
        case '*': return 1;
        case '^': return 2;
    }
    return -1;
}



stack* infix_to_postfix(const char *x) {
    stack *head1 = NULL;
    stack *head2 = NULL;
    stack *ans = NULL;
    char *input = strdup(x);
    char *token = strtok(input, " ");
    int a = 0;

    while (token != NULL) {
        char *endptr;
        double val = strtod(token, &endptr);
        if (endptr != token && *endptr == '\0') {
            push(&head1, val,'n');
        } else {
            if (strlen(token) == 1) {
                // 2 + 3 * 4 -> 3 4 * 2 +
                // 2 * 3 + 4 -> 2 3 * 4 +
                // if (token[0] == '(') {
                //     a += 1;
                // } else if (token[0] == ')') {
                //     a -= 1;
                // }
                while (head2 && priority(token[0]) < priority(head2->type)) {
                    if (is_empty(ans)) {
                        push(&ans,head1->value,'n');
                        pop_num(&head1);
                    }
                    push(&ans,head1->value,'n');
                    pop_num(&head1);
                    push(&ans,0,head2->type);
                    pop_type(&head2);
                }
                push(&head2,0,token[0]);
            }
        }
        token = strtok(NULL, " ");
    }
    while (head2) {
        if (is_empty(ans)) {
            push(&ans,head1->value,'n');
            pop_num(&head1);
        }
        push(&ans,head1->value,'n');
        pop_num(&head1);
        push(&ans,0,head2->type);
        pop_type(&head2);
    }
    return ans;
}



stack* newlist(stack *head) {
    stack **newlist = &head;
    head = head -> next;
    while (head != NULL) {
        push(newlist, head -> value, head -> type);
        head = head -> next;
    }
    return *newlist;
}



double postfix_notation(stack *poliz) {
    stack *head = NULL;
    stack *plz = newlist(poliz);

    while (plz -> next != NULL) { // какое условие сюда вписать чтобы закончилось когда
        // не будет следующего эл списка
        if (!(is_type(&plz))) {
            push(&head, plz -> value, plz -> type);
        } else {
            double b = pop_num(&head);
            double a = pop_num(&head);
            switch (head -> type) {
                case '+': push(&head, a + b, 'n'); break;
                case '-': push(&head, a - b, 'n'); break;
                case '*': push(&head, a * b, 'n'); break;
                case '^': push(&head, pow(a, b), 'n'); break;
                default:
                    printf("Unknown operator\n");
                    return 0.0;
            }
        }
        plz = plz -> next;
    }
    double result = pop_num(&head);
    if (!is_empty(head)) {
        printf("Incorrect input\n");
    }
    return result;
}

int main() {
    printf("%.2lf\n", postfix_notation(infix_to_postfix("2 + 3 * 4")));
    return 0;
}