#include "projectHeaders.h"

// modules
#include "compareArrNum.c"
#include "diffArrNum.c"

struct numbersStruct {
    int firstNumArr[MAX_LENGTH], secondNumArr[MAX_LENGTH];
    char firstNum[MAX_LENGTH], secondNum[MAX_LENGTH];
    int firstNumSign, secondNumSign;
} numbersS;

// select which operation user wants to
int selectOperationFunc();

// get numbers from user and store these numbers to a struct
struct numbersStruct getNumbersFunc();

// checking number's sign
void checkNumSign(char *num, int *whichNum);

// convert numbers gotten from user to an array and return it
int *convertNumToArr(char *num);

// multiply two numbers based on arrays
void multiplyFunc(char *num1, char *num2);

// divide two numbers based on arrays
void divideFunc(int *x, int *y);

// print a string of numbers
void printCharNumArr(char *arr);

// checking if incoming int array is zero or not
int isArrNumZero(int *num);

// entry point to start application
int main() {

    int op;

    system("clear");

    // select which operation user wants (op == 1 means multiplication / op == 2 means division)
    op = selectOperationFunc();

    if (op == 1) {
        // get numbers from user to divide them
        struct numbersStruct multiplyNumbers = getNumbersFunc(op);

        multiplyFunc(multiplyNumbers.firstNum, multiplyNumbers.secondNum);
    } else if (op == 2) {
        // get numbers from user to divide them
        struct numbersStruct divideNumbers = getNumbersFunc(op);

        divideFunc(divideNumbers.firstNumArr, divideNumbers.secondNumArr);
    } else
        puts("Please select correct operation!");

    return 0;
}

int selectOperationFunc() {
    int opNum = 1;

    puts("Hello, \nThis project is created by YASIN GOURKANI (yassingourkani@outlook.com)\n\nPlease enter the number of operation you want to do:");
    puts("1. Multiplication");
    puts("2. Division");
    scanf("%d", &opNum);

    printf("\nYou selected: %d\n\n", opNum);

    return opNum;
}

struct numbersStruct getNumbersFunc() {

    // positive init numbers
    numbersS.firstNumSign = 0;
    numbersS.secondNumSign = 0;

    // empty number arrays
    for (int i = 0; i < MAX_LENGTH; i++) {
        numbersS.firstNum[i] = ' ';
        numbersS.secondNum[i] = ' ';
    }

    // get first number from user
    puts("Enter first number: ");
    scanf("%s", numbersS.firstNum);
    checkNumSign(numbersS.firstNum, &numbersS.firstNumSign);

    if (numbersS.firstNum[0] == '-' || numbersS.firstNum[0] == '+')
        numbersS.firstNum[0] = '0';

    int *r1 = convertNumToArr(numbersS.firstNum);

    // assign first number to array
    for (int i = (MAX_LENGTH - 1); i >= 0; i--) {
        numbersS.firstNumArr[i] = r1[i];
    }

    // get second number from user
    puts("Enter second number: ");
    scanf("%s", numbersS.secondNum);
    checkNumSign(numbersS.secondNum, &numbersS.secondNumSign);

    if (numbersS.secondNum[0] == '-' || numbersS.secondNum[0] == '+')
        numbersS.secondNum[0] = '0';

    int *r2 = convertNumToArr(numbersS.secondNum);

    // assign second number to array
    for (int i = 0; i < MAX_LENGTH; i++) {
        numbersS.secondNumArr[i] = r2[i];
    }

    return numbersS;
}

void checkNumSign(char *num, int *whichNum) {
    if (num[0] == '-')
        *whichNum = 1;
}

int *convertNumToArr(char *num) {

    static int arr[MAX_LENGTH] = {0};
    int charCounter;

    // initialize arr items for new usage (since arr is static and is have not valid items for next usages)
    for (int i = 0; i < MAX_LENGTH; i++) {
        arr[i] = 0;
    }

    // counter for counting valid number of stringNum (ignore 0 created by null or \0 of string)
    for (charCounter = 0;
         charCounter < MAX_LENGTH && num[charCounter] >= 48 && num[charCounter] <= 57; charCounter++);

    // separate number which was segmented to string to each item of arr
    int j = 0;
    for (int i = (MAX_LENGTH - charCounter); i < MAX_LENGTH; i++) {
        if (num[j] >= 48 && num[j] <= 57) {
            arr[i] = num[j] - 48;
        }
        j++;
    }

    puts("");
    return arr;
}

void multiplyFunc(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    if (len1 == 0 || len2 == 0) {
        printf("0");
        return;
    }

    int result[MAX_NUMBERS_SIZE] = {0};

    int iNum1 = 0, iNum2;

    // Go from right to left in num1
    for (int i = (len1 - 1); i >= 0; i--) {
        int carry = 0;
        int n1 = num1[i] - 48;

        iNum2 = 0;

        for (int j = len2 - 1; j >= 0; j--) {
            int n2 = num2[j] - 48;

            int sum = n1 * n2 + result[iNum1 + iNum2] + carry;

            carry = sum / 10;

            result[iNum1 + iNum2] = sum % 10;

            iNum2++;
        }

        if (carry > 0)
            result[iNum1 + iNum2] += carry;

        iNum1++;
    }

    int resultSize, i;
    resultSize = i = (sizeof(result) / sizeof(result[0])) - 1;
    while (i >= 0 && result[i] == 0) {
        i--;
        resultSize--;
    };

    if (i == -1) {
        printf("0");
        return;
    }

    // final result of multiply on string
    static char resultOnStr[MAX_NUMBERS_SIZE] = {};

    while (i >= 0) {
        resultOnStr[(resultSize - 1) - i] = result[i--] + 48;
    }

    if ((numbersS.firstNumSign == 1 && numbersS.secondNumSign == 1) ||
        (numbersS.firstNumSign == 0 && numbersS.secondNumSign == 0)) // for positive result
        printf("The result is: +%s\n\n", resultOnStr);
    else // for negative result
        printf("The result is: -%s\n\n", resultOnStr);
}

void divideFunc(int *x, int *y) {

    int quotient = 0, firstChecking = 0, r;
    char remain[MAX_LENGTH] = "";

    firstChecking = compareArrNum(x, y, MAX_LENGTH); // x > y

    if (firstChecking == 1) { // x > y
        r = isArrNumZero(y);

        // show the result is infinite
        if (r == 1) {
            printf("\nThe result is INFINITE\n\n");

            return;
        }
    } else if (firstChecking == -1) {
        r = isArrNumZero(x);

        // show the result is zero
        if (r == 1) {
            printf("\nThe result is ZERO\n\n");

            return;
        }
    }

    while (1) {
        if (compareArrNum(x, y, MAX_LENGTH) == -1) { // x < y

            // assign reminder
            for (int i = (MAX_LENGTH - 1); i >= 0; i--) {
                remain[i] = x[i] + 48;
            }

            break;
        }

        x = diffArrNum(x, y);

        quotient++;
    }

    if ((numbersS.firstNumSign == 1 && numbersS.secondNumSign == 1) ||
        (numbersS.firstNumSign == 0 && numbersS.secondNumSign == 0)) // for positive result
        printf("\nQuotient: +%d , remain: ", quotient);
    else
        printf("\nQuotient: -%d , remain: ", quotient);
    printCharNumArr(remain);
    puts("\n");
}

void printCharNumArr(char *arr) {
    int flag = 0;

    for (int i = 0; i < MAX_LENGTH; i++) {
        if (arr[i] == '0' && flag == 0) {
            continue;
        }

        flag = 1;
        printf("%c", arr[i]);
    }
}

int isArrNumZero(int *num) {

    int i = 0, flag = 1;

    while (i < MAX_LENGTH) {

        // flag will be 0, if the number is NOT quite zero
        if (num[i] != 0) {
            flag = 0;
            break;
        }
        i++;
    }

    return flag;
};