#include "bigint_operations.h"
#include <stdio.h>
#include <stdlib.h>

void initBigInt(BigInt* num) {
    num->head = NULL;
}

void insertDigit(BigInt* num, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = digit;
    newNode->next = num->head;
    num->head = newNode;
}

void addBigInts(BigInt* num1, BigInt* num2, BigInt* result) {
    int carry = 0;
    Node* ptr1 = num1->head;
    Node* ptr2 = num2->head;

    while (ptr1 != NULL || ptr2 != NULL || carry != 0) {
        int sum = carry;
        if (ptr1 != NULL) {
            sum += ptr1->data;
            ptr1 = ptr1->next;
        }
        if (ptr2 != NULL) {
            sum += ptr2->data;
            ptr2 = ptr2->next;
        }
        carry = sum / 10;
        sum = sum % 10;
        insertDigit(result, sum);
    }
}

void subtractBigInts(BigInt* num1, BigInt* num2, BigInt* result) {
    int borrow = 0;
    Node* ptr1 = num1->head;
    Node* ptr2 = num2->head;

    while (ptr1 != NULL || ptr2 != NULL || borrow != 0) {
        int diff = borrow;
        if (ptr1 != NULL) {
            diff += ptr1->data;
            ptr1 = ptr1->next;
        }
        if (ptr2 != NULL) {
            diff -= ptr2->data;
            ptr2 = ptr2->next;
        }
        if (diff < 0) {
            borrow = -1;
            diff += 10;
        } else {
            borrow = 0;
        }
        insertDigit(result, diff);
    }
}

void displayReversedBigInt(BigInt* num) {
    Node* current = num->head;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

void clearBigInt(BigInt* num) {
    Node* current = num->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    num->head = NULL;
}
