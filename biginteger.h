#ifndef BIGINT_H
#define BIGINT_H
struct Node
{
    int data;
    struct Node *next, *prev;
};
struct Node *createNode(int);
struct Node *numToNode(char []);
struct Node *reverse(struct Node *);
struct Node *bigintAdd(char [], char []);
struct Node *bigintSubtract(char [], char []);
struct Node *bigintMultiply(char [], char []);
int lengthNode(struct Node *);
int isFirstNumGOE(struct Node *, struct Node *);
struct Node *bigintDivide(char [], char []);
struct Node *bigintModulus(char [], char []);
void display(struct Node *);
#endif
