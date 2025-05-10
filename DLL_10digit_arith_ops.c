#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int digit;
    struct Node* prev;
    struct Node* next;
};

struct Node* insertEnd(struct Node* head, int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->digit = digit;
    newNode->prev = NULL;
    newNode->next = NULL;

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

struct Node* insertFront(struct Node* head, int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->digit = digit;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL)
        head->prev = newNode;

    return newNode;
}

struct Node* createFromInput(char* numStr) {
    struct Node* head = NULL;
    int len = strlen(numStr);
    for (int i = 0; i < len; i++) {
        if (numStr[i] >= '0' && numStr[i] <= '9') {
            head = insertEnd(head, numStr[i] - '0');
        }
    }
    return head;
}

void printList(struct Node* head) {
    // Skip leading zeros
    while (head && head->digit == 0 && head->next) {
        head = head->next;
    }
    while (head != NULL) {
        printf("%d", head->digit);
        head = head->next;
    }
    printf("\n");
}

struct Node* getLast(struct Node* head) {
    while (head && head->next != NULL)
        head = head->next;
    return head;
}

int compare(struct Node* a, struct Node* b) {
    while (a && a->digit == 0) a = a->next;
    while (b && b->digit == 0) b = b->next;

    int len1 = 0, len2 = 0;
    struct Node* t;

    for (t = a; t; t = t->next) len1++;
    for (t = b; t; t = t->next) len2++;

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    while (a && b) {
        if (a->digit > b->digit) return 1;
        if (a->digit < b->digit) return -1;
        a = a->next;
        b = b->next;
    }
    return 0;
}

struct Node* add(struct Node* a, struct Node* b) {
    struct Node* res = NULL;
    struct Node *lastA = getLast(a), *lastB = getLast(b);
    int carry = 0;

    while (lastA != NULL || lastB != NULL || carry) {
        int sum = carry;
        if (lastA != NULL) {
            sum += lastA->digit;
            lastA = lastA->prev;
        }
        if (lastB != NULL) {
            sum += lastB->digit;
            lastB = lastB->prev;
        }
        carry = sum / 10;
        res = insertFront(res, sum % 10);
    }

    return res;
}

struct Node* subtract(struct Node* a, struct Node* b) {
    if (compare(a, b) < 0) {
        printf("Error: Negative result not supported.\n");
        return NULL;
    }

    struct Node* res = NULL;
    struct Node *lastA = getLast(a), *lastB = getLast(b);
    int borrow = 0;

    while (lastA != NULL) {
        int d1 = lastA->digit - borrow;
        int d2 = (lastB != NULL) ? lastB->digit : 0;

        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        res = insertFront(res, d1 - d2);

        lastA = lastA->prev;
        if (lastB) lastB = lastB->prev;
    }

    return res;
}

struct Node* multiply(struct Node* a, struct Node* b) {
    int lenA = 0, lenB = 0;
    struct Node* t;

    for (t = a; t; t = t->next) lenA++;
    for (t = b; t; t = t->next) lenB++;

    int* result = (int*)calloc(lenA + lenB, sizeof(int));

    struct Node *pa = getLast(a), *pb;
    int i = 0;

    while (pa != NULL) {
        int carry = 0, d1 = pa->digit;
        pb = getLast(b);
        int j = 0;
        while (pb != NULL) {
            int d2 = pb->digit;
            int mul = d1 * d2 + result[i + j] + carry;
            carry = mul / 10;
            result[i + j] = mul % 10;
            pb = pb->prev;
            j++;
        }
        if (carry > 0)
            result[i + j] += carry;
        pa = pa->prev;
        i++;
    }

    struct Node* res = NULL;
    int start = lenA + lenB - 1;
    while (start > 0 && result[start] == 0) start--;  // Skip leading 0s

    for (int k = start; k >= 0; k--) {
        res = insertEnd(res, result[k]);
    }

    free(result);
    return res;
}

int main() {
    char num1[20], num2[20];
    printf("Enter first number (max 10 digits): ");
    scanf("%s", num1);
    printf("Enter second number (max 10 digits): ");
    scanf("%s", num2);

    struct Node* head1 = createFromInput(num1);
    struct Node* head2 = createFromInput(num2);

    int choice;
    do {
        printf("\nMenu:\n1. Add\n2. Subtract\n3. Multiply\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        struct Node* result = NULL;

        switch (choice) {
            case 1:
                result = add(head1, head2);
                printf("Sum = ");
                printList(result);
                break;
            case 2:
                result = subtract(head1, head2);
                if (result) {
                    printf("Difference = ");
                    printList(result);
                }
                break;
            case 3:
                result = multiply(head1, head2);
                printf("Product = ");
                printList(result);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
