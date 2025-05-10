#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Node* mergeSortedDLL(struct Node* l1, struct Node* l2) {
    struct Node* merged = NULL;
    struct Node* tail = NULL;

    while (l1 && l2) {
        struct Node* temp;
        if (l1->data <= l2->data) {
            temp = l1;
            l1 = l1->next;
        } else {
            temp = l2;
            l2 = l2->next;
        }
        temp->prev = temp->next = NULL;

        if (merged == NULL) {
            merged = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    while (l1) {
        struct Node* temp = l1;
        l1 = l1->next;
        temp->next = NULL;
        temp->prev = NULL;
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }

    while (l2) {
        struct Node* temp = l2;
        l2 = l2->next;
        temp->next = NULL;
        temp->prev = NULL;
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }

    return merged;
}

int main() {
    int n1, n2, val;
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    printf("Enter number of elements in first sorted list: ");
    scanf("%d", &n1);
    printf("Enter %d sorted elements:\n", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        list1 = insertEnd(list1, val);
    }

    printf("Enter number of elements in second sorted list: ");
    scanf("%d", &n2);
    printf("Enter %d sorted elements:\n", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        list2 = insertEnd(list2, val);
    }

    struct Node* merged = mergeSortedDLL(list1, list2);

    printf("Merged sorted list: ");
    display(merged);

    return 0;
}
