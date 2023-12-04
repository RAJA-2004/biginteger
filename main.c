#include <stdio.h>
#include <stdlib.h>
#include "biginteger.h"

int main()
{
    struct Node *result;
    char num1[1000], num2[1000];

    int choice;
    do
    {
    label:
        printf("\n");
        printf("1 for addition\n2 for subtraction\n3 for multiplication\n4 for division\n5 for bigintModulus\n6 to stop\n-->");
        scanf("%d", &choice);
        if (choice == 6)
        {
            printf("\nThank you :)\n");
            printf("Exiting...\n");
            exit(0);
        }
        else if (choice > 0 && choice < 6)
        {
            printf("\n");
            printf("Enter first number: ");
            scanf("%s", num1);
            printf("Enter second number: ");
            scanf("%s", num2);

            switch (choice)
            {
            case 1:
            {
                result = bigintAdd(num1, num2);
                printf("%s + %s = ", num1, num2);
                display(result);
                break;
            }
            case 2:
            {
                result = bigintSubtract(num1, num2);
                printf("%s - %s = ", num1, num2);
                display(result);
                break;
            }
            case 3:
            {
                result = bigintMultiply(num1, num2);
                printf("%s * %s = ", num1, num2);
                display(result);
                break;
            }
            case 4:
            {
                result = bigintDivide(num1, num2);
                printf("%s / %s = ", num1, num2);
                display(result);
                break;
            }
            case 5:
            {
                result = bigintModulus(num1, num2);
                printf("%s %% %s = ", num1, num2);
                display(result);
                break;
            }
            default:
                printf("Wrong input!!\n");
            }
        }
        else
            printf("Wrong input!!!\n");
        while (1)
        {

            printf("\nDo you want to perform again\n1 for yes\n2 for no\n-->");
            scanf("%d", &choice);
            if (choice == 1)
                goto label;
            else if (choice == 2)
            {
                printf("\nThank you :)\n");
                printf("Exiting...\n");
                exit(0);
            }
            else
                printf("Wrong input!!!\n");
        }
    } while (choice != 6);

    return 0;
}