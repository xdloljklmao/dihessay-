#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Add to rear (Enqueue)
struct Node* enqueue(struct Node* rear, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = rear;

    if (rear != NULL)
        rear->next = newNode;

    rear = newNode;
    printf("Enqueued: %d\n", value);
    return rear;
}

// Delete from front (Dequeue)
struct Node* dequeue(struct Node* front) {
    if (front == NULL) {
        printf("Queue Underflow\n");
        return NULL;
    }

    printf("Dequeued: %d\n", front->data);
    struct Node* temp = front;
    front = front->next;
    if (front != NULL)
        front->prev = NULL;
    free(temp);
    return front;
}

// Display queue from front to rear
void display(struct Node* front) {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue (front to rear): ");
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* front = NULL;
    struct Node* rear = NULL;
    int choice, value;

    while (1) {
        printf("\nMenu:\n1. Enqueue (Add)\n2. Dequeue (Delete)\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            rear = enqueue(rear, value);
            if (front == NULL)  // First node
                front = rear;
        } else if (choice == 2) {
            front = dequeue(front);
            if (front == NULL)  // Queue became empty
                rear = NULL;
        } else if (choice == 3) {
            display(front);
        } else if (choice == 4) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
