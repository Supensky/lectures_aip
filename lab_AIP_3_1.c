#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node* createNode(int data) {
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insert(node **head_ref, int data) {
    node* new_node = createNode(data);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

int calc_in_postfix(node *head) {
    int ans = 0;
    for (node* curr = head; curr != NULL; curr = curr->next) {
        for (node *temp = curr; temp != NULL; temp = temp->next) {
            if (curr->data > temp->data) {
                ans++;
            }
        }
    }
    return ans;
}

void display(node *head_ref) {
    node *temp = head_ref;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

void display_last_k(node *head_ref, int k) {
    node *temp = head_ref;
    k--;
    while (temp != NULL && k!=0) {
        printf("%d\n", temp->data);
        temp = temp->next;
        k--;
    }
}

node* deepCopy(node *head_ref) {
    node *newlist = createNode(head_ref->data);
    head_ref = head_ref->next;
    while (head_ref != NULL) {
        insert(&newlist, head_ref->data);
        head_ref = head_ref->next;
    }
    return newlist;
}

void deepfree(node *head_ref) {
    if (head_ref != NULL) {
        deepfree(head_ref->next);
        free(head_ref);
    }
}

void insert_sort(node **head_ref) {
    node *sorted = NULL;
    node *curr = *head_ref;
    while (curr != NULL) {
        node *next = curr->next;
        if (sorted == NULL || curr->data < sorted -> data) {
            curr->next = sorted;
            sorted = curr;
        } else {
            node *t = sorted;
            while (t->next != NULL && t->next->data < curr -> data) {
                t = t->next;
            }
            curr->next = t->next;
            t->next = curr;
        }
        curr = next;
    }
    *head_ref = sorted;
}

int main(void) {
    node *head = NULL;
    int x = 1;
    while (scanf("%d", &x) != EOF) {
        insert(&head, x);
    }
    display(head);
    printf("INVERS %d\n", calc_in_postfix(head));
    node *temp = deepCopy(head);
    display(temp);
    insert_sort(&temp);
    display(temp);
    deepfree(temp);
    deepfree(head);
    return 0;
}