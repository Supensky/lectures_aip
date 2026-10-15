#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Stack {
    double value;
    char type;
    struct Stack *next;
} stack;

stack *init_stack(double value, char type) {
    stack *s = (stack *)malloc(sizeof(stack));
    s->value = value;
    s->next = NULL;
    s->type = type;
    return s;
}

int is_empty(stack *s) {
    return s == NULL;
}

double pop_num(stack **head) {
    if (!is_empty(*head)) {
        stack *temp = *head;
        double val = temp->value;
        *head = (*head)->next;
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
        double val = temp->type;
        *head = (*head)->next;
        free(temp);
        return val;
    } else {
        printf("Stack is empty\n");
    }
}

int is_type(stack **head) {
    if (!is_empty(*head)) {
        if ((*head)->type == 'n') {
            return 0;
        } else {
            return 1;
        }
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}

void push(stack **head, double val, char type) {
    stack *newstack = init_stack(val, type);
    newstack->next = *head;
    *head = newstack;
}

int priority(stack *a) {
    int deep_level = a->value;
    switch (a->type) {
        case '+': return 0 + deep_level * 6;
        case '-': return 0 + deep_level * 6;
        case '*': return 1 + deep_level * 6;
        case '^': return 2 + deep_level * 6;
    }
    return -1;
}



stack *infix_to_postfix(char *x) {
    stack *head1 = NULL;
    stack *head2 = NULL;
    if (x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
    }
    int deep_level = 0;
    stack *ans = NULL;
    char *input = strdup(x);
    char *token = strtok(input, " ");
    int a = 0;

    while (token != NULL) {
        char *endptr;
        double val = strtod(token, &endptr);

        if (endptr != token && *endptr == '\0') {
            push(&head1, val, 'n');
            token = strtok(NULL, " ");
            continue;
        }
        if (token[0] == '(') {
            deep_level++;
            token = strtok(NULL, " ");
            continue;
        }  if (token[0] == ')') {
            deep_level--;
            token = strtok(NULL, " ");
            continue;
        }
         {
            if (strlen(token) == 1) {
                stack *tmp = init_stack(deep_level, token[0]);
                while (head2 && priority(tmp) < priority(head2)) {
                    if (is_empty(ans)) {
                        push(&ans, head1->value, 'n');
                        pop_num(&head1);
                    }
                    push(&ans, head1->value, 'n');
                    pop_num(&head1);
                    push(&ans, deep_level, head2->type);
                    pop_type(&head2);
                }
                free(tmp);
                push(&head2, deep_level, token[0]);
            }
        }
        token = strtok(NULL, " ");
    }
    while (head2) {
        if (is_empty(ans)) {
            push(&ans, head1->value, 'n');
            pop_num(&head1);
        }
        push(&ans, head1->value, 'n');
        pop_num(&head1);
        push(&ans, deep_level, head2->type);
        pop_type(&head2);
    }
    return ans;
}


stack *newlist(stack *head) {
    stack *newlist = init_stack(head->value, head->type);
    head = head->next;
    while (head != NULL) {
        push(&newlist, head->value, head->type);
        head = head->next;
    }
    return newlist;
}


double postfix_notation(stack *poliz) {
    stack *head = NULL;
    stack *plz = newlist(poliz);
    while (plz != NULL) {
        push(&head, plz->value, plz->type);
        if (is_type(&head)) {
            char oper = pop_type(&head);
            double b = pop_num(&head);
            double a = pop_num(&head);
            switch (oper) {
                case '+': push(&head, a + b, 'n');
                    break;
                case '-': push(&head, a - b, 'n');
                    break;
                case '*': push(&head, a * b, 'n');
                    break;
                case '^': push(&head, pow(a, b), 'n');
                    break;
                default:
                    printf("Unknown operator\n");
                    return 0.0;
            }
        }
        plz = plz->next;
    }
    double result = pop_num(&head);
    if (!is_empty(head)) {
        printf("Incorrect input\n");
    }
    return result;
}

int main() {
    char buf[100];
    fgets(buf, 100, stdin);
    printf("%.2lf\n", postfix_notation(infix_to_postfix(buf)));
    return 0;
}
