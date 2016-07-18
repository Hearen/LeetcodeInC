#include"utils.h"


void main()
{
    int numbers[SIZE];
    randomIntArray(numbers, SIZE, 0, MAX);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
    printf("After sorting:\n***********************\n");
    bubbleSort1(numbers, SIZE);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
}
