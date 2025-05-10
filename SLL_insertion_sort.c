#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Insert in sorted order
struct Node* sortedInsert(struct Node* head, struct Node* newNode) {
    if (head == NULL || newNode->data < head->data) {
        newNode->next = head;
        return newNode;
    }

    struct Node* current = head;
    while (current->next != NULL && current->next->data < newNode->data)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;
    return head;
}

// Perform Insertion Sort
struct Node* insertionSort(struct Node* head) {
    struct Node* sorted = NULL;
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        current->next = NULL;
        sorted = sortedInsert(sorted, current);
        current = next;
    }
    return sorted;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL, *temp, *tail = NULL;
    int n, i, val;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        temp->data = val;
        temp->next = NULL;
        if (head == NULL) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    head = insertionSort(head);
    printf("Sorted list (Insertion Sort): ");
    display(head);
    return 0;
}
