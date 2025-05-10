#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int digit;
    struct Node *next;
};

void insert(struct Node **head, int digit) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->digit = digit;
    newNode->next = *head;
    *head = newNode;
}

struct Node* reverse(struct Node *head) {
    struct Node *prev = NULL, *curr = head, *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void printNumber(struct Node *head) {
    while (head) {
        printf("%d", head->digit);
        head = head->next;
    }
    printf("\n");
}

struct Node* numberToList(char number[]) {
    struct Node *head = NULL;
    for (int i = strlen(number) - 1; i >= 0; i--) {
        insert(&head, number[i] - '0');
    }
    return head;
}

struct Node* addLists(struct Node *l1, struct Node *l2) {
    struct Node *result = NULL;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry > 0) {
        int sum = carry;
        if (l1) {
            sum += l1->digit;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->digit;
            l2 = l2->next;
        }

        insert(&result, sum % 10);
        carry = sum / 10;
    }

    return reverse(result);
}

struct Node* subtractLists(struct Node *l1, struct Node *l2) {
    struct Node *result = NULL;
    int borrow = 0;

    while (l1 != NULL) {
        int diff = l1->digit - borrow - (l2 ? l2->digit : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        insert(&result, diff);

        l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return reverse(result);
}

struct Node* multiplyLists(struct Node *l1, struct Node *l2) {
    int result[20] = {0}; // supports up to 10-digit * 10-digit = 20-digit result
    int i = 0, j;

    for (struct Node *a = l1; a != NULL; a = a->next, i++) {
        j = 0;
        for (struct Node *b = l2; b != NULL; b = b->next, j++) {
            result[i + j] += a->digit * b->digit;
        }
    }

    for (i = 0; i < 19; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    // Remove leading zeros
    for (i = 19; i > 0 && result[i] == 0; i--);

    struct Node *head = NULL;
    for (; i >= 0; i--) {
        insert(&head, result[i]);
    }

    return head;
}

// Simple division: treat as integers
void divideNumbers(char num1[], char num2[]) {
    long long n1 = atoll(num1);
    long long n2 = atoll(num2);

    if (n2 == 0) {
        printf("Error: Division by zero\n");
        return;
    }

    printf("Quotient: %lld\n", n1 / n2);
    printf("Remainder: %lld\n", n1 % n2);
}

int main() {
    int choice;
    char num1[11], num2[11];

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        printf("Enter first number (max 10 digits): ");
        scanf("%10s", num1);
        printf("Enter second number (max 10 digits): ");
        scanf("%10s", num2);

        struct Node *list1 = numberToList(num1);
        struct Node *list2 = numberToList(num2);
        struct Node *result = NULL;

        switch (choice) {
            case 1:
                result = addLists(list1, list2);
                printf("Sum: ");
                printNumber(result);
                break;
            case 2:
                result = subtractLists(list1, list2);
                printf("Difference: ");
                printNumber(result);
                break;
            case 3:
                result = multiplyLists(list1, list2);
                printf("Product: ");
                printNumber(result);
                break;
            case 4:
                divideNumbers(num1, num2);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
