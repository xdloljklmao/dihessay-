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

// Sorted insert
void SortedInsert(struct Node** head, struct Node* newNode) {
    // If list is empty or newNode should be placed at the start
    if (*head == NULL || (*head)->data >= newNode->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // Find the position to insert
    struct Node* current = *head;
    while (current->next != NULL && current->next->data < newNode->data) {
        current = current->next;
    }

    // Insert newNode at the correct position
    newNode->next = current->next;
    current->next = newNode;
}

// Display list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* newNode;
    int n, value;

    // Input number of elements in the sorted list
    printf("Enter the number of elements in the sorted list: ");
    scanf("%d", &n);

    // Input sorted list elements
    printf("Enter %d sorted elements in increasing order:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        newNode = createNode(value);
        SortedInsert(&head, newNode);
    }

    printf("Original sorted list: \n");
    display(head);

    // Input new value to be inserted
    printf("Enter a value to insert into the sorted list: ");
    scanf("%d", &value);
    newNode = createNode(value);
    SortedInsert(&head, newNode);

    printf("List after insertion: \n");
    display(head);

    return 0;
}
