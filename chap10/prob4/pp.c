#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory Error\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
    printf("%d\n", data);
}

int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "Stack is Empty\n");
        exit(EXIT_FAILURE);
    }
    struct node *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}int main() {
    struct node *top = NULL;

    push(&top, 55);
    push(&top, 606);
    push(&top, 808);
    push(&top, 818);
    push(&top, (double)2.3);
    printf("Print stack\n");
    printf("%d\n",pop(&top));
    printf("%d\n",pop(&top));
    printf("%d\n",pop(&top));
    printf("%d\n",pop(&top));
    printf("%d\n",pop(&top));
}
