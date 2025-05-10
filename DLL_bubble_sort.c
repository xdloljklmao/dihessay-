#include <stdio.h>
#include <stdlib.h>

struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};

void swap(struct DNode* a, struct DNode* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void bubbleSort(struct DNode* head) {
    int swapped;
    struct DNode* ptr;
    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != NULL) {
            if (ptr->data > ptr->next->data) {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}

void displayD(struct DNode* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct DNode* head = NULL, *tail = NULL, *temp;
    int n, val;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        temp = (struct DNode*)malloc(sizeof(struct DNode));
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        temp->data = val;
        temp->next = NULL;
        temp->prev = tail;
        if (tail != NULL)
            tail->next = temp;
        else
            head = temp;
        tail = temp;
    }

    bubbleSort(head);
    printf("Sorted list (Bubble Sort): ");
    displayD(head);
    return 0;
}
