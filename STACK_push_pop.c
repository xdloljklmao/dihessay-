#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Push operation (Insert at beginning)
struct Node* push(struct Node* top, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = top;

    if (top != NULL)
        top->prev = newNode;

    top = newNode;
    printf("Pushed: %d\n", value);
    return top;
}

// Pop operation (Delete from beginning)
struct Node* pop(struct Node* top) {
    if (top == NULL) {
        printf("Stack empty\n");
        return NULL;
    }

    printf("Popped: %d\n", top->data);
    struct Node* temp = top;
    top = top->next;

    if (top != NULL)
        top->prev = NULL;

    free(temp);
    return top;
}

// Display stack
void display(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack (top to bottom): ");
    struct Node* temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* top = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value to push: ");
            scanf("%d", &value);
            top = push(top, value);
        } else if (choice == 2) {
            top = pop(top);
        } else if (choice == 3) {
            display(top);
        } else if (choice == 4) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
