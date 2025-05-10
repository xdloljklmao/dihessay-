#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void Append(struct Node** a, struct Node** b) {
    if (*a == NULL) {
        *a = *b;
    } else {
        struct Node* temp = *a;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *b;
    }
    *b = NULL;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* buildList() {
    int n, value;
    struct Node *head = NULL, *tail = NULL;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

int main() {
    struct Node *a = NULL, *b = NULL;

    printf("Enter elements for List A:\n");
    a = buildList();

    printf("\nEnter elements for List B:\n");
    b = buildList();

    printf("\nList A before append: ");
    printList(a);

    printf("List B before append: ");
    printList(b);

    Append(&a, &b);

    printf("\nList A after append: ");
    printList(a);

    printf("List B after append: ");
    printList(b);

    return 0;
}
