#ifndef BIGINT_OPERATIONS_H
#define BIGINT_OPERATIONS_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct BigInt {
    Node* head;
} BigInt;

void initBigInt(BigInt* num);
void insertDigit(BigInt* num, int digit);
void addBigInts(BigInt* num1, BigInt* num2, BigInt* result);
void subtractBigInts(BigInt* num1, BigInt* num2, BigInt* result); // Added subtraction function
void displayReversedBigInt(BigInt* num);
void clearBigInt(BigInt* num);

#endif
