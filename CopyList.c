#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *next;
};

// Function to append a node at the end
void append(struct Node **head, int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Function to copy the list
struct Node* CopyList(struct Node *originalHead) {
    if (originalHead == NULL) return NULL;

    struct Node *newHead = NULL, *tail = NULL, *current = originalHead;

    while (current != NULL) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = current->data;
        newNode->next = NULL;

        if (newHead == NULL) {
            newHead = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        current = current->next;
    }

    return newHead;
}

// Function to print the list
void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL)
            printf(" -> ");
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

int main() {
    struct Node *original = NULL;
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &val);
        append(&original, val);
    }

    printf("\nOriginal List: ");
    printList(original);

    struct Node *copied = CopyList(original);

    printf("Copied List: ");
    printList(copied);

    return 0;
}
