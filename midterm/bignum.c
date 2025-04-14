#include <stdio.h>
#include <string.h>
#define MAX 200

// Function to check if a number is negative
int is_negative(const char number[]) {
    return number[0] == '-';
}

// Function to compare two numbers as strings (ignoring sign)
int compare(const char number1[], const char number2[]) {
    int length1 = strlen(number1);
    int length2 = strlen(number2);
    if (length1 > length2) return 1;
    if (length1 < length2) return -1;
    return strcmp(number1, number2);
}

// Function to add two large numbers
void add(const char number1[], const char number2[], char result[]) {
    int isNegative1 = is_negative(number1);
    int isNegative2 = is_negative(number2);

    if (isNegative1 && isNegative2) {  // (-A) + (-B) = -(A + B)
        char sum[MAX + 1];
        add(number1 + 1, number2 + 1, sum);
        result[0] = '-';
        strcpy(result + 1, sum);
        return;
    } else if (isNegative1) {  // (-A) + B = B - A
        subtract(number2, number1 + 1, result);
        return;
    } else if (isNegative2) {  // A + (-B) = A - B
        subtract(number1, number2 + 1, result);
        return;
    }

    int length1 = strlen(number1);
    int length2 = strlen(number2);
    int carry = 0, index1, index2, resultIndex = 0;
    char tempResult[MAX + 1];

    index1 = length1 - 1;
    index2 = length2 - 1;

    while (index1 >= 0 || index2 >= 0 || carry) {
        int digit1 = (index1 >= 0) ? number1[index1] - '0' : 0;
        int digit2 = (index2 >= 0) ? number2[index2] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        tempResult[resultIndex++] = (sum % 10) + '0';
        carry = sum / 10;
        index1--, index2--;
    }
    tempResult[resultIndex] = '\0';

    for (index1 = 0; index1 < resultIndex; index1++)
        result[index1] = tempResult[resultIndex - index1 - 1];

    result[resultIndex] = '\0';
}

// Function to subtract two large numbers
void subtract(const char number1[], const char number2[], char result[]) {
    int isNegative1 = is_negative(number1);
    int isNegative2 = is_negative(number2);

    if (isNegative1 && isNegative2) {  // (-A) - (-B) = B - A
        subtract(number2 + 1, number1 + 1, result);
        return;
    } else if (isNegative1) {  // (-A) - B = -(A + B)
        char sum[MAX + 1];
        add(number1 + 1, number2, sum);
        result[0] = '-';
        strcpy(result + 1, sum);
        return;
    } else if (isNegative2) {  // A - (-B) = A + B
        add(number1, number2 + 1, result);
        return;
    }

    int comparison = compare(number1, number2);
    if (comparison == 0) {
        strcpy(result, "0");
        return;
    }

    int isNegativeResult = 0;
    const char *largerNumber = number1, *smallerNumber = number2;
    if (comparison < 0) { // Swap if number1 < number2
        isNegativeResult = 1;
        largerNumber = number2;
        smallerNumber = number1;
    }

    int length1 = strlen(largerNumber);
    int length2 = strlen(smallerNumber);
    int borrow = 0, index1, index2, resultIndex = 0;
    char tempResult[MAX + 1];

    index1 = length1 - 1;
    index2 = length2 - 1;

    while (index1 >= 0 || index2 >= 0) {
        int digit1 = (index1 >= 0) ? largerNumber[index1] - '0' : 0;
        int digit2 = (index2 >= 0) ? smallerNumber[index2] - '0' : 0;

        if (borrow) {
            if (digit1 > 0) {
                digit1--;
                borrow = 0;
            } else {
                digit1 = 9;
                borrow = 1;
            }
        }
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        }
        tempResult[resultIndex++] = (digit1 - digit2) + '0';
        index1--, index2--;
    }

    while (resultIndex > 1 && tempResult[resultIndex - 1] == '0') resultIndex--; // Remove leading zeros
    tempResult[resultIndex] = '\0';

    for (index1 = 0; index1 < resultIndex; index1++)
        result[index1] = tempResult[resultIndex - index1 - 1];

    result[resultIndex] = '\0';

    if (isNegativeResult) {
        memmove(result + 1, result, resultIndex + 1);
        result[0] = '-';
    }
}

// Function to multiply two large numbers
void multiply(const char number1[], const char number2[], char result[]) {
    int isNegative1 = is_negative(number1);
    int isNegative2 = is_negative(number2);
    char absNumber1[MAX + 1], absNumber2[MAX + 1];

    if (isNegative1) strcpy(absNumber1, number1 + 1);
    else strcpy(absNumber1, number1);

    if (isNegative2) strcpy(absNumber2, number2 + 1);
    else strcpy(absNumber2, number2);

    int length1 = strlen(absNumber1);
    int length2 = strlen(absNumber2);
    int product[MAX * 2] = {0};

    for (int index1 = length1 - 1; index1 >= 0; index1--) {
        for (int index2 = length2 - 1; index2 >= 0; index2--) {
            int multiplication = (absNumber1[index1] - '0') * (absNumber2[index2] - '0');
            int pos1 = index1 + index2, pos2 = index1 + index2 + 1;
            int sum = multiplication + product[pos2];
            product[pos2] = sum % 10;
            product[pos1] += sum / 10;
        }
    }

    int resultIndex = 0, index = 0;
    while (index < length1 + length2 && product[index] == 0) index++;

    if (index == length1 + length2) strcpy(result, "0");
    else {
        if (isNegative1 ^ isNegative2) result[resultIndex++] = '-';
        while (index < length1 + length2) result[resultIndex++] = product[index++] + '0';
        result[resultIndex] = '\0';
    }
}

int main() {
    char number1[MAX + 1], number2[MAX + 1], sum[MAX + 1], difference[MAX + 1], product[MAX * 2 + 1];

    // Read input
    scanf("%s", number1);
    scanf("%s", number2);

    // Perform calculations
    add(number1, number2, sum);
    subtract(number1, number2, difference);
    multiply(number1, number2, product);

    // Print results
    printf("%s\n", sum);
    printf("%s\n", difference);
    printf("%s\n", product);

    return 0;
}

