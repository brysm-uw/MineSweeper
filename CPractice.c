//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int add(int, int);
int subtract(int, int);
int multiply(int, int);
double divide(double, double);
int main()
{
    bool input = true;
    for (;;) {
        if (input == false) {
            return 0;
        }
        else {
            printf("\nSelect an option (0 to exit): ");
            printf("\n1. Add two numbers");
            printf("\n2. Subtract two numbers");
            printf("\n3. Multiply two numbers");
            printf("\n4. Divide two numbers\n");

            int option = 0;
            int n1 = 0;
            int n2 = 0;
            double lf1 = 0.0;
            double lf2 = 0.0;

            scanf("%d", &option);

            if (option == 0) {
                return 0;
            }
            else if (option == 4) {
                printf("Enter first number: ");
                scanf("%d", &lf1);
                printf("Enter second number: ");
                scanf("%d", &lf2);
            }
            else {
                printf("Enter first number: ");
                scanf("%d", &n1);
                printf("Enter second number: ");
                scanf("%d", &n2);
            }
            switch (option) {
            case 0:
                input = false;
                break;
            case 1:
                printf("Answer: %d", add(n1, n2));
                break;
            case 2:
                printf("Answer: %d", subtract(n1, n2));
                break;
            case 3:
                printf("Answer: %d", multiply(n1, n2));
                break;
            case 4:
                printf("Answer: %lf", divide(lf1, lf2));
                printf("\n");
                break;
            default:
                printf("Input not expected.\n");
                return 0;
                break;
            }
        }
    }
    return 0;
}
int add(int num1, int num2) {
    return num1 + num2;
}
int subtract(int num1, int num2) {
    return num1 - num2;
}
int multiply(int num1, int num2) {
    return num1 * num2;
}
double divide(double num1, double num2) {
    if (num2 == 0.0) {
        printf("cannot divide by 0");
        exit(1);
    }
    return num1 / num2;
}