#include "projectHeaders.h"

int *diffArrNum(int *arr1, int *arr2);

int *diffArrNum(int *arr1, int *arr2) {

    static int result[MAX_LENGTH] = {0};

    for (int i = (MAX_LENGTH - 1); i >= 0; i--) {
        if (arr1[i] >= arr2[i]) {
            result[i] = arr1[i] - arr2[i];
        } else {
            arr1[i - 1]--;
            arr1[i] += 10;
            result[i] = arr1[i] - arr2[i];
        }
    }

    return result;
}