#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Function to insert term in sorted order and combine like powers
struct Node* insertTerm(struct Node* head, int coeff, int power) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;

    if (head == NULL || power > head->power) {
        newNode->next = head;
        return newNode;
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->power >= power) {
        if (temp->power == power) {
            temp->coeff += coeff;
            free(newNode);
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    newNode->next = temp;
    prev->next = newNode;
    return head;
}

// Function to display the polynomial
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->power);
        if (temp->next != NULL) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node *head1 = NULL, *head2 = NULL, *head3 = NULL;
    int n1, n2, coeff, power;

    // Input Polynomial 1
    printf("Enter number of terms in polynomial 1: ");
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        printf("Enter coefficient and power of term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        head1 = insertTerm(head1, coeff, power);
    }

    // Input Polynomial 2
    printf("Enter number of terms in polynomial 2: ");
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        printf("Enter coefficient and power of term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        head2 = insertTerm(head2, coeff, power);
    }

    // Add Polynomials
    struct Node *p1 = head1, *p2 = head2;
    while (p1 != NULL) {
        head3 = insertTerm(head3, p1->coeff, p1->power);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        head3 = insertTerm(head3, p2->coeff, p2->power);
        p2 = p2->next;
    }

    // Output result
    printf("Sum of polynomials: ");
    display(head3);

    return 0;
}
