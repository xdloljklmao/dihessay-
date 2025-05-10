#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Create new node
struct Node* createNode(int coeff, int power) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Append term to polynomial
void appendTerm(struct Node** head, int coeff, int power) {
    if (coeff == 0) return;

    struct Node* newNode = createNode(coeff, power);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        struct Node* prev = NULL;
        while (temp != NULL && temp->power > power) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL && temp->power == power) {
            temp->coeff += coeff;
            free(newNode);
        } else {
            if (prev == NULL) {
                newNode->next = *head;
                *head = newNode;
            } else {
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
    }
}

// Print polynomial
void printPoly(struct Node* head) {
    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->power);
        if (head->next != NULL) printf(" + ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;
    int n1, n2, coeff, power;

    printf("Enter number of terms in polynomial 1: ");
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        printf("Enter coefficient and power of term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        appendTerm(&poly1, coeff, power);
    }

    printf("Enter number of terms in polynomial 2: ");
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        printf("Enter coefficient and power of term %d: ", i + 1);
        scanf("%d %d", &coeff, &power);
        appendTerm(&poly2, coeff, power);
    }

    // Multiply polynomials
    struct Node* t1 = poly1;
    while (t1 != NULL) {
        struct Node* t2 = poly2;
        while (t2 != NULL) {
            appendTerm(&result, t1->coeff * t2->coeff, t1->power + t2->power);
            t2 = t2->next;
        }
        t1 = t1->next;
    }

    printf("Product of polynomials: ");
    printPoly(result);

    return 0;
}
