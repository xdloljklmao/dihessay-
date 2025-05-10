#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) return newNode;

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

// Append list1 to start of list2
struct Node* appendStart(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    struct Node* tail1 = list1;
    while (tail1->next != NULL)
        tail1 = tail1->next;

    tail1->next = list2;
    list2->prev = tail1;

    return list1;  // list1 becomes new head
}

// Append list1 to end of list2
struct Node* appendEnd(struct Node* list1, struct Node* list2) {
    if (list2 == NULL) return list1;
    if (list1 == NULL) return list2;

    struct Node* tail2 = list2;
    while (tail2->next != NULL)
        tail2 = tail2->next;

    tail2->next = list1;
    list1->prev = tail2;

    return list2;  // list2 remains head
}

int main() {
    struct Node *list1 = NULL, *list2 = NULL;
    int n1, n2, val;

    printf("Enter number of elements in List 1: ");
    scanf("%d", &n1);
    printf("Enter %d elements for List 1:\n", n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        list1 = insertEnd(list1, val);
    }

    printf("Enter number of elements in List 2: ");
    scanf("%d", &n2);
    printf("Enter %d elements for List 2:\n", n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        list2 = insertEnd(list2, val);
    }

    printf("\nChoose:\n1. Append List 1 to START of List 2\n2. Append List 1 to END of List 2\nEnter choice: ");
    int choice;
    scanf("%d", &choice);

    struct Node* result = NULL;
    if (choice == 1)
        result = appendStart(list1, list2);
    else if (choice == 2)
        result = appendEnd(list1, list2);
    else {
        printf("Invalid choice.\n");
        return 0;
    }

    printf("Resulting list: ");
    display(result);

    return 0;
}
