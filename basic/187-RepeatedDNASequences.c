/*******************************************
Author: LHearen
E-mail: LHearen@126.com
Time  :	2015-12-13 21:00
Description: 
Source: https://leetcode.com/problems/repeated-dna-sequences/
*******************************************/
#include <stdlib.h>
//AC - 4ms - beating 100%;
//since there are only 4 different letter we need to distinguish, so enumeration or something similar can perfectly handle this case;
//given A - 65, C - 67, G - 71, T - 84;
//(X - 'A' + 1)%5 will be 1, 3, 2, 0 and can be represented by only two-bits!
//10 letters can be represented by 20-bits which is smaller than 32 bits of an integer;
//Bang! We can then handle it using bit manipulation by just traversing one single round.
char** findRepeatedDnaSequences(char*s, int* returnSize)
{
    int size = strlen(s);
    if(size < 11) return NULL; //at least 11 letters;
    char hashTable[1<<21] = {0}; //allocate a hash map array for 20-bit key;
    int hashNum = 0;
    int index = 0;
    char** sArray = (char**)malloc(sizeof(char*) * size);
    for(int i = 0; i < 9; i++) //the head of the first key;
        hashNum = hashNum << 2 | (*(s+i) - 'A' + 1) % 5;
    for(int i = 9; i < size; i++) //one step forward, one different string will be covered by the key simply;
    {
        if(hashTable[hashNum = (hashNum << 2 | (*(s+i) - 'A' + 1) % 5) & 0xfffff]++ == 1) //each repeated substring will only be collected once;
        {
            sArray[index] = (char*)malloc(11 * sizeof(char));
            strncpy(sArray[index], s+i-9, 10);
            sArray[index++][10] = '\0';
        }
    }
    *returnSize = index;
    return sArray;
}
