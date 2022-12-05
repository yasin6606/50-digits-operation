// compare to int array (! both of they must have same length which this length will get on arrSize)
// if firstArr is greater that secondArr this function return 1 and in other side return, -1 and if they are same, return 0
int compareArrNum(int *firstArr, int *secondArr, int arrSize) {

    int flag = 0;

    for (int i = 0; i < arrSize; i++) {
        if (firstArr[i] == secondArr[i]) {
            continue;
        } else if (firstArr[i] > secondArr[i]) {
            flag = 1;
            break;
        } else {
            flag = -1;
            break;
        }
    }

    return flag;
};
