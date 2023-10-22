#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biginteger.h"

struct Node *createNode(int value)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if (!temp)
        return NULL;
    temp->data = value;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

struct Node *reverse(struct Node *head)
{
    if (!head)
        return NULL;
    struct Node *newList = NULL, *temp;
    while (head)
    {
        temp = createNode(head->data);
        if (!newList)
        {
            newList = temp;
        }
        else
        {
            temp->next = newList;
            newList->prev = temp;
            newList = temp;
        }
        head = head->next;
    }
    return newList;
}

struct Node *numToNode(char num[])
{
    struct Node *head = NULL, *temp;
    int i, charToNum;

    int negative = 0;
    for (i = 0; i < strlen(num); i++)
    {
        if (num[i] == '-')
        {
            negative = 1;
            i++;
        }
        if (negative)
        {
            charToNum = -1 * ((int)num[i] - 48);
        }
        else
        {
            charToNum = (int)num[i] - 48;
        }
        temp = createNode(charToNum);
        if (!head)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }
    return head;
}

struct Node *revertSign(struct Node *head)
{
    struct Node *itr = head;
    while (itr)
    {
        itr->data = -1 * itr->data;
        itr = itr->next;
    }
    return head;
}

int lengthNode(struct Node *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

int isFirstNumGOE(struct Node *temp1, struct Node *temp2)
{
    while(temp1->data==0 && temp1->next!=NULL) 
    {   
        temp1 = temp1->next;
    }
    if (lengthNode(temp1) > lengthNode(temp2))
        return 1;
    if (lengthNode(temp1) < lengthNode(temp2))
        return 0;
    if (lengthNode(temp1) == lengthNode(temp2))
    {
        while (temp1 != NULL)
        {
            if (temp1->data > temp2->data)
            {
                return 1;
            }
            if (temp1->data < temp2->data)
            {
                return 0;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return 2; 
}

struct Node *bigintAdd(char numb1[], char numb2[])
{
    struct Node *result = NULL, *temp, *itr;
    struct Node *num1 = numToNode(numb1);
    struct Node *num2 = numToNode(numb2);

    int len1 = strlen(numb1) - 1;
    int len2 = strlen(numb2) - 1;
    if (numb1[0] == '-')
        len1--;
    if (numb2[0] == '-')
        len2--;

    int reverted = 0;

    if (len1 == len2)
    {
        if (numb1[0] == '-' && numb2[0] == '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (numb1[i] > numb2[i])
                    break;
                if (numb1[i] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }

        else if (numb1[0] == '-' && numb2[0] != '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1) 
            {
                if (numb1[i] > numb2[i - 1])
                    break;
                if (numb1[i] < numb2[i - 1])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
            else
            {
                num1 = revertSign(num1);
                num2 = revertSign(num2);
                reverted = 1;
            }
        }

        else if (numb1[0] != '-' && numb2[0] == '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (numb1[i - 1] > numb2[i])
                    break;
                if (numb1[i - 1] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
                reverted = 1;
            }
        }

        else if ((numb1[0] < numb2[0]) && (numb1[0] != '-' && numb2[0] != '-')) 
        {
            struct Node *temp = num1;
            num1 = num2;
            num2 = temp;
        }
        else if ((numb1[0] == numb2[0]) && (numb1[0] != '-' && numb2[0] != '-'))
        {
            int i = 1, flag = 0;
            while (i < len1)
            {
                if (numb1[i] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }
    }

    else if (len1 < len2) 
    {
        struct Node *temp = num1;
        num1 = num2;
        num2 = temp;
        if (numb1[0] != '-' && numb2[0] == '-') 
        {
            num1 = revertSign(num1);
            num2 = revertSign(num2);
            reverted = 1;
        }
    }

    num1 = reverse(num1);
    num2 = reverse(num2);
    if (num1->data < 0)
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
        reverted = 1;
    }
    num1 = reverse(num1);
    num2 = reverse(num2);

    if (!num1)
    {
        result = num2;
        return result;
    }
    if (!num2)
    {
        result = num1;
        return result;
    }
    if (!num1 && !num2)
        return NULL;

    while (num1 && num2)
    {
        if ((num1->data + num2->data < 0) && (num1->data >= 0 || num2->data >= 0))
        {
            struct Node *itr = num1->next;
            while (itr->data == 0)
                itr = itr->next;
            itr->data = itr->data - 1;
            while (itr != num1)
            {
                itr = itr->prev;
                if (itr == num1)
                    break;
                itr->data = itr->data + 10 - 1;
            }
            num1->data = num1->data + 10;
        }

        temp = createNode(num1->data + num2->data);
        if (!result)
        {
            result = temp;
            itr = result;
        }
        else
        {
            itr->next = temp;
            temp->prev = itr;
            if (itr->data > 9 || itr->data < -9)
            {
                temp->data = temp->data + itr->data / 10; 
                itr->data = itr->data % 10;
            }
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }
    while (num1)
    {
        temp = createNode(num1->data);
        if (itr->data > 9 || itr->data < -9)
        {
            temp->data = temp->data + itr->data / 10;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num1 = num1->next;
    }
    while (num2)
    {
        temp = createNode(num2->data);
        if (itr->data > 9 || itr->data < -9)
        {
            temp->data = temp->data + itr->data / 10;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num2 = num2->next;
    }

    if (reverted)
    {
        result = revertSign(result);
    }
    return result;
}

struct Node *bigintSubtract(char numb1[], char numb2[])
{
    struct Node *result = NULL, *temp, *itr;
    struct Node *num1 = numToNode(numb1);
    struct Node *num2 = numToNode(numb2);

    int isAnswerNegative = 0;
    if (isFirstNumGOE(num1, num2))
    {
        isAnswerNegative = 0;
    }
    if (isFirstNumGOE(num2, num1))
    {
        isAnswerNegative = 1;
    }
    int len1 = strlen(numb1) - 1;
    int len2 = strlen(numb2) - 1;
    if (numb1[0] == '-')
        len1--;
    if (numb2[0] == '-')
        len2--;

    if (len1 == len2)
    {
        if (numb1[0] == '-' && numb2[0] == '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (numb1[i] > numb2[i])
                    break;
                if (numb1[i] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
            }
        }

        else if (numb1[0] == '-' && numb2[0] != '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (numb1[i] > numb2[i - 1])
                    break;
                if (numb1[i] < numb2[i - 1])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }

        else if (numb1[0] != '-' && numb2[0] == '-')
        {
            int i = 1, flag = 0;
            while (i < len1 + 1)
            {
                if (numb1[i - 1] > numb2[i])
                    break;
                if (numb1[i - 1] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
                num1 = revertSign(num1);
                num2 = revertSign(num2);
            }
        }

        else if ((numb1[0] < numb2[0]) && (numb1[0] != '-' && numb2[0] != '-'))
        {
            struct Node *temp = num1;
            num1 = num2;
            num2 = temp;
        }

        else if ((numb1[0] == numb2[0]) && (numb1[0] != '-' && numb2[0] != '-'))
        {
            int i = 1, flag = 0;
            while (i < len1)
            {
                if (numb1[i] < numb2[i])
                {
                    flag = 1;
                    break;
                }
                i++;
            }
            if (flag == 1)
            {
                struct Node *temp = num1;
                num1 = num2;
                num2 = temp;
            }
        }
    }

    else if (len1 < len2) 
    {
        struct Node *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    num1 = reverse(num1);
    num2 = reverse(num2);
    if (num1->data < 0)
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }
    num1 = reverse(num1);
    num2 = reverse(num2);

    if (!num1)
    {
        result = num2;
        return result;
    }
    if (!num2)
    {
        result = num1;
        return result;
    }
    if (!num1 && !num2)
    {
        return NULL;
    }

    while (num1 && num2)
    {
        if (num1->data < num2->data)
        {
            struct Node *itr = num1->next;
            while (itr->data == 0)
            {
                itr = itr->next;
            }
            itr->data = itr->data - 1;
            while (itr != num1)
            {
                itr = itr->prev;
                if (itr == num1)
                    break;
                itr->data = itr->data + 10 - 1;
            }
            num1->data = num1->data + 10;
        }

        temp = createNode(num1->data - num2->data);

        if (!result)
        {
            result = temp;
            itr = result;
        }
        else
        {
            itr->next = temp;
            temp->prev = itr;
            if (itr->data < -9 || itr->data > 9)
            {
                temp->data = temp->data + itr->data / 10;
                itr->data = itr->data % 10;
            }
            itr = itr->next;
        }
        num1 = num1->next;
        num2 = num2->next;
    }

    while (num1)
    {
        temp = createNode(num1->data);
        if (itr->data < -9 || itr->data > 9)
        {
            temp->data = temp->data + itr->data / 10;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num1 = num1->next;
    }

    while (num2)
    {
        temp = createNode(num2->data);
        if (itr->data < -9 || itr->data > 9)
        {
            temp->data = temp->data + itr->data / 10;
            itr->data = itr->data % 10;
        }
        temp->prev = itr;
        itr->next = temp;
        itr = itr->next;
        num2 = num2->next;
    }

    if (isAnswerNegative == 1)
        result = revertSign(result);
    return result;
}

struct Node *bigintMultiply(char numb1[], char numb2[])
{
    struct Node *result = NULL, *resultItr;
    struct Node *num1 = numToNode(numb1);
    struct Node *num2 = numToNode(numb2); 
    struct Node *num1Pointer = num1;
    struct Node *num2Pointer = num2;

    int isNegative = 0;
    if (numb1[0] == '-' && numb2[0] != '-')
    {
        num1 = revertSign(num1);
        isNegative = 1;
    }
    if (numb1[0] != '-' && numb2[0] == '-')
    {
        num2 = revertSign(num2);
        isNegative = 1;
    }
    if (numb1[0] == '-' && numb2[0] == '-')
    {
        num1 = revertSign(num1);
        num2 = revertSign(num2);
        isNegative = 0;
    }

    struct Node *temp1 = NULL, *temp2 = NULL;
    struct Node *temp1ptr, *temp2ptr;
    while (num2Pointer != NULL)
    {
        if (temp1 == NULL)
        {
            while (num1Pointer != NULL) 
            {
                struct Node *newNode = createNode(num1Pointer->data * num2Pointer->data);
                if (temp1 == NULL)
                {
                    temp1 = newNode;
                    temp1ptr = temp1;
                }
                else
                {
                    if (temp1ptr->data > 9)
                    {
                        newNode->data = newNode->data + temp1ptr->data / 10;
                        temp1ptr->data = temp1ptr->data % 10;
                    }
                    newNode->prev = temp1ptr;
                    temp1ptr->next = newNode;
                    temp1ptr = temp1ptr->next;
                }
                num1Pointer = num1Pointer->next;
            }
            if (temp1ptr->data > 9)
            {
                struct Node *newNode = createNode(temp1ptr->data / 10);
                temp1ptr->data = temp1ptr->data % 10;
                newNode->prev = temp1ptr;
                temp1ptr->next = newNode;
            }

            num1Pointer = num1;
            num2Pointer = num2Pointer->next;
        }

        if (num2Pointer != NULL)
        {
            temp2 = NULL;
            while (num1Pointer != NULL)
            {
                struct Node *newNode = createNode(num1Pointer->data * num2Pointer->data);
                if (temp2 == NULL)
                {
                    temp2 = newNode;
                    temp2ptr = temp2;
                }
                else
                {
                    if (temp2ptr->data > 9)
                    {
                        newNode->data = newNode->data + temp2ptr->data / 10;
                        temp2ptr->data = temp2ptr->data % 10;
                    }
                    newNode->prev = temp2ptr;
                    temp2ptr->next = newNode;
                    temp2ptr = temp2ptr->next;
                }
                num1Pointer = num1Pointer->next;
            }
            if (temp2ptr->data > 9)
            {
                struct Node *newNode = createNode(temp2ptr->data / 10);
                temp2ptr->data = temp2ptr->data % 10;
                newNode->prev = temp2ptr;
                temp2ptr->next = newNode;
            }
            num1Pointer = num1;
            num2Pointer = num2Pointer->next;
        }

        struct Node *temp = createNode(temp1->data);
        struct Node *itr = temp1;
        temp1 = temp1->next;
        free(itr);
        if (temp1 != NULL)
            temp1->prev = NULL;

        if (result == NULL)
        {
            result = temp;
            resultItr = result;
        }
        else
        {
            
            temp->prev = resultItr;
            resultItr->next = temp;
            resultItr = resultItr->next;
        }

        
        if (temp2 != NULL)
        {
            struct Node *forSwapping = temp1;
            temp1 = temp2;
            temp2 = forSwapping;
        }

        temp1ptr = temp1, temp2ptr = temp2; 
        struct Node *sumOfTemps = NULL, *sumItr;
        
        while (temp1ptr != NULL && temp2ptr != NULL)
        {
            struct Node *newNode = createNode(temp1ptr->data + temp2ptr->data);
            if (sumOfTemps == NULL)
            {
                sumOfTemps = newNode;
                sumItr = sumOfTemps;
            }
            else
            {
                if (sumItr->data > 9)
                {
                    newNode->data = newNode->data + sumItr->data / 10;
                    sumItr->data = sumItr->data % 10;
                }
                newNode->prev = sumItr;
                sumItr->next = newNode;
                sumItr = sumItr->next;
            }
            temp1ptr = temp1ptr->next;
            temp2ptr = temp2ptr->next;
        }

        while (temp1ptr != NULL)
        {
            struct Node *newNode = createNode(temp1ptr->data);
            if (sumOfTemps == NULL)
            {
                sumOfTemps = newNode;
                sumItr = sumOfTemps;
            }
            else
            {
                if (sumItr->data > 9)
                {
                    newNode->data = newNode->data + sumItr->data / 10;
                    sumItr->data = sumItr->data % 10;
                }
                newNode->prev = sumItr;
                sumItr->next = newNode;
                sumItr = sumItr->next;
            }
            temp1ptr = temp1ptr->next;
        }

        temp1 = sumOfTemps;
    }

    while (temp1 != NULL)
    {
        struct Node *newNode = createNode(temp1->data);
        newNode->prev = resultItr;
        resultItr->next = newNode;
        resultItr = resultItr->next;
        temp1 = temp1->next;
    }

    if (isNegative)
        result = revertSign(result);
    return result;
}

struct Node *bigintDivide(char numb1[], char numb2[])
{
    struct Node *result = NULL;
    struct Node *num1 = numToNode(numb1);
    struct Node *num2 = numToNode(numb2);

    int isNegativeAnswer = 0;
    if (numb1[0] == '-' && numb2[0] != '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
    }
    if (numb1[0] != '-' && numb2[0] == '-')
    {
        isNegativeAnswer = 1;
        num2 = revertSign(num2);
    }
    if (numb1[0] == '-' && numb2[0] == '-')
    {
        isNegativeAnswer = 0;
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }

    num1 = reverse(num1);
    num2 = reverse(num2);

    if (num1->data == 0) 
        return NULL;
    if (num2->data == 0)
    {
        struct Node *newNode = createNode(999); 
        result = newNode;                         
        return result;
    }

    int lenOfNum1 = lengthNode(num1);
    int lenOfNum2 = lengthNode(num2);

    if (lenOfNum1 < lenOfNum2) 
    {
        return result;
    }

    if (lenOfNum1 == lenOfNum2) 
    {
        int isNum1Greater = 2;
        struct Node *num1Pointer = num1, *num2Pointer = num2;
        while (num1Pointer != NULL)
        {
            if (num1Pointer->data > num2Pointer->data)
            {
                isNum1Greater = 1;
                break;
            }
            if (num1Pointer->data < num2Pointer->data)
            {
                isNum1Greater = 0;
                break;
            }
            num1Pointer = num1Pointer->next;
            num2Pointer = num2Pointer->next;
        }
        if (isNum1Greater == 0) 
        {
            return result; 
        }
    }

    struct Node *rem = NULL, *remPtr;
    int extract = 1;
    struct Node *temp = NULL, *tempPtr;

    while (num1 != NULL)
    {
        int count = 0;
        int i = 0;
        while (i < lenOfNum2 && extract == 1) 
        {
            struct Node *newNode = createNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPtr = temp;
            }
            else
            {
                newNode->prev = tempPtr;
                tempPtr->next = newNode;
                tempPtr = tempPtr->next;
            }
            struct Node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
            i++;
        }

        if (extract == 0)
        {
            struct Node *newNode = createNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPtr = temp;
            }
            else
            {
                while (tempPtr->next != NULL)
                {
                    tempPtr = tempPtr->next;
                }
                newNode->prev = tempPtr;
                tempPtr->next = newNode;
                tempPtr = tempPtr->next;
            }
            struct Node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
        }

        while (isFirstNumGOE(temp, num2))
        {
            temp = reverse(temp);
            num2 = reverse(num2);

            struct Node *num2Pointer = num2;
            tempPtr = temp;

            while (tempPtr != NULL && num2Pointer != NULL)
            {
                if (tempPtr->data < num2Pointer->data) 
                {
                    struct Node *itr = tempPtr->next;
                    while (itr->data == 0)
                    {
                        itr = itr->next;
                    }
                    itr->data = itr->data - 1;
                    while (itr != tempPtr)
                    {
                        itr = itr->prev;
                        if (itr == tempPtr)
                        {
                            break;
                        }
                        itr->data = itr->data + 10 - 1;
                    }
                    tempPtr->data = tempPtr->data + 10;
                }

                struct Node *newNode = createNode(tempPtr->data - num2Pointer->data);

                if (rem == NULL)
                {
                    rem = newNode;
                    remPtr = rem;
                }
                else
                {
                    newNode->prev = remPtr;
                    remPtr->next = newNode;
                    remPtr = remPtr->next;
                }
                tempPtr = tempPtr->next;
                num2Pointer = num2Pointer->next;
            }
            while (tempPtr != NULL)
            {
                struct Node *newNode = createNode(tempPtr->data);
                if (rem == NULL)
                {
                    rem = newNode;
                    remPtr = rem;
                }
                else
                {
                    newNode->prev = remPtr;
                    remPtr->next = newNode;
                    remPtr = remPtr->next;
                }
                tempPtr = tempPtr->next;
            }

            rem = reverse(rem);
            while (rem->data == 0 && rem->next != NULL)
            {
                struct Node *forFreeing = rem;
                rem = rem->next;
                free(forFreeing);
                forFreeing = NULL;
            }

            remPtr = rem;
            temp = rem;
            rem = NULL;
            count++;
            tempPtr = temp;
            num2 = reverse(num2);
            num2Pointer = num2;
        }

        if (extract == 1 && count > 0)
        {
            struct Node *newNode = createNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        else if (extract == 0)
        {
            struct Node *newNode = createNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        extract = 0;
    }

    if (isNegativeAnswer == 1)
        result = revertSign(result);
    return result;
}

struct Node *bigintModulus(char numb1[], char numb2[])
{
    struct Node *num1 = numToNode(numb1);
    struct Node *num2 = numToNode(numb2);

    int isNegativeAnswer = 0;
    if (numb1[0] == '-' && numb2[0] != '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
    }
    if (numb1[0] != '-' && numb2[0] == '-')
    {
        isNegativeAnswer = 0;
        num2 = revertSign(num2);
    }
    if (numb1[0] == '-' && numb2[0] == '-')
    {
        isNegativeAnswer = 1;
        num1 = revertSign(num1);
        num2 = revertSign(num2);
    }

    num1 = reverse(num1);
    num2 = reverse(num2);
    struct Node *result = NULL;

    if (num2->data == 0)
    {
        struct Node *newNode = createNode(999);
        result = newNode;                       
        return result;
    }

    if (isFirstNumGOE(num1, num2) == 0)
    {
        num1 = reverse(num1);
        result = num1;
        if (isNegativeAnswer == 1)
            result = revertSign(result);
        return result;
    }

    int lenOfNum1 = lengthNode(num1);
    int lenOfNum2 = lengthNode(num2);

    if (lenOfNum1 < lenOfNum2) 
    {
        return result;
    }

    if (lenOfNum1 == lenOfNum2)
    {
        int isNum1Greater = 2;
        struct Node *num1Pointer = num1, *num2Pointer = num2;
        while (num1Pointer != NULL)
        {
            if (num1Pointer->data > num2Pointer->data)
            {
                isNum1Greater = 1;
                break;
            }
            if (num1Pointer->data < num2Pointer->data)
            {
                isNum1Greater = 0;
                break;
            }
            num1Pointer = num1Pointer->next;
            num2Pointer = num2Pointer->next;
        }
        if (isNum1Greater == 0)
        {
            return result;
        }
    }

    struct Node *rem = NULL, *remPtr;
    int extract = 1;
    struct Node *temp = NULL, *tempPtr;

    while (num1 != NULL)
    {
        int count = 0;
        int i = 0;
        while (i < lenOfNum2 && extract == 1)
        {
            struct Node *newNode = createNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPtr = temp;
            }
            else
            {
                newNode->prev = tempPtr;
                tempPtr->next = newNode;
                tempPtr = tempPtr->next;
            }
            struct Node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
            i++;
        }

        if (extract == 0)
        {
            struct Node *newNode = createNode(num1->data);
            if (temp == NULL)
            {
                temp = newNode;
                tempPtr = temp;
            }
            else
            {
                while (tempPtr->next != NULL)
                {
                    tempPtr = tempPtr->next;
                }
                newNode->prev = tempPtr;
                tempPtr->next = newNode;
                tempPtr = tempPtr->next;
            }
            struct Node *forFreeing = num1;
            num1 = num1->next;
            free(forFreeing);
            forFreeing = NULL;
        }

        while (isFirstNumGOE(temp, num2))
        {
            temp = reverse(temp); 
            num2 = reverse(num2);

            struct Node *num2Pointer = num2;
            tempPtr = temp;

            while (tempPtr != NULL && num2Pointer != NULL)
            {
                if (tempPtr->data < num2Pointer->data)
                {
                    struct Node *itr = tempPtr->next;
                    while (itr->data == 0)
                    {
                        itr = itr->next;
                    }
                    itr->data = itr->data - 1;
                    while (itr != tempPtr)
                    {
                        itr = itr->prev;
                        if (itr == tempPtr)
                        {
                            break;
                        }
                        itr->data = itr->data + 10 - 1;
                    }
                    tempPtr->data = tempPtr->data + 10;
                }

                struct Node *newNode = createNode(tempPtr->data - num2Pointer->data);

                if (rem == NULL)
                {
                    rem = newNode;
                    remPtr = rem;
                }
                else
                {
                    newNode->prev = remPtr;
                    remPtr->next = newNode;
                    remPtr = remPtr->next;
                }
                tempPtr = tempPtr->next;
                num2Pointer = num2Pointer->next;
            }
            while (tempPtr != NULL)
            {
                struct Node *newNode = createNode(tempPtr->data);
                if (rem == NULL)
                {
                    rem = newNode;
                    remPtr = rem;
                }
                else
                {
                    newNode->prev = remPtr;
                    remPtr->next = newNode;
                    remPtr = remPtr->next;
                }
                tempPtr = tempPtr->next;
            }

            rem = reverse(rem);
            while (rem->data == 0 && rem->next != NULL)
            {
                struct Node *forFreeing = rem;
                rem = rem->next;
                free(forFreeing);
                forFreeing = NULL;
            }

            remPtr = rem;
            temp = rem;
            rem = NULL;
            count++;
            tempPtr = temp; 
            num2 = reverse(num2);
            num2Pointer = num2;
        }

        if (extract == 1 && count > 0)
        {
            struct Node *newNode = createNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        else if (extract == 0)
        {
            struct Node *newNode = createNode(count);
            if (result == NULL)
            {
                result = newNode;
            }
            else
            {
                result->prev = newNode;
                newNode->next = result;
                result = newNode;
            }
        }
        extract = 0; 
    }

    result = reverse(temp);
    if (isNegativeAnswer == 1)
        result = revertSign(result);
    return result;
}

void display(struct Node *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }
    head = reverse(head);
    if (head->data == 0)
    {
        while (head->data == 0 && head->next != NULL)
        {
            head = head->next;
        }
    }

    if (head->data < 0)
    {
        struct Node *itr = head->next;
        while (itr != NULL)
        {
            if (itr->data < 0)
                itr->data = -1 * itr->data;
            itr = itr->next;
        }
    }

    if (head->data == 999)
    {
        printf("Can't bigintDivide by zero!!!\n");
        return;
    }
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}
