#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

node *init_node(int data) {
    node *s = (node *)malloc(sizeof(node));
    if (s == NULL) {
        perror("Malloc failed");
        exit(1);
    }
    s -> data = data;
    s -> next = NULL;
    return s;
}

void push(node **head, int val) {
    node *newnode = init_node(val);
    newnode -> next = *head;
    *head = newnode;
}

int calc_k(node *head) {
    int k = 0;
    for (node *first = head; first != NULL; first = first -> next) {
        for (node *second = first; second != NULL; second = second -> next) {
            if (first->data > second->data) k++;
        }
    }
    return k;
}

void print_k(node *head) {
    node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}

node* newlist(node *head) {
    if (head == NULL) return NULL;

    node *nl = init_node(head->data);
    head = head -> next;
    while (head != NULL) {
        push(&nl, head->data);
        head = head -> next;
    }
    return nl;
}


void free_node(node *head) {
    if (head != NULL) {
        free_node(head -> next);
        free(head);
    }
}

void insert_sort(node **head) {
    node *s = NULL;
    node *temp = *head;
    while (temp != NULL) {
        node *next = temp -> next;
        if (s == NULL || temp -> data < s -> data) {
            temp -> next = s;
            s = temp;
        } else {
            node *cur = s;
            while (cur -> next != NULL && cur -> next -> data < temp -> data) {
                cur = cur -> next;
            }
            temp -> next = cur -> next;
            cur -> next = temp;
        }
        temp = next;
    }
    *head = s;
}

int main() {
    node *head = NULL;
    int a = 1;

    while (scanf("%d", &a) == 1) {
        push(&head, a);
    }

    printf("Original list: ");
    print_k(head);

    printf("Invers: %d\n", calc_k(head));

    node *temp = newlist(head);
    insert_sort(&temp);

    printf("Sorted list: ");
    print_k(temp);

    free_node(temp);
    free_node(head);
    return 0;
}
