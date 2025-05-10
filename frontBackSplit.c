#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Print the list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

// Split the list into front and back halves
void frontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    int length = 0;
    struct Node* temp = source;

    // Count length
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    // Edge case: list has 0 or 1 node
    if (length < 2) {
        *frontRef = source;
        *backRef = NULL;
        return;
    }

    int mid = (length + 1) / 2; // front gets extra if odd
    struct Node* current = source;
    *frontRef = source;

    for (int i = 1; i < mid; i++) {
        current = current->next;
    }

    *backRef = current->next;
    current->next = NULL;
}

int main() {
    int n, value;
    struct Node *head = NULL, *tail = NULL;

    printf("Enter number of elements in the list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        struct Node* newNode = createNode(value);

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    struct Node* front = NULL;
    struct Node* back = NULL;

    frontBackSplit(head, &front, &back);

    printf("\nFront half: ");
    printList(front);

    printf("Back half: ");
    printList(back);

    return 0;
}
