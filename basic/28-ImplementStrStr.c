/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 15:38
Description : Implement strStr().
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
Source      : https://leetcode.com/problems/implement-strstr/
*******************************************/
//AC - 0ms
int strStr0(char* haystack, char* needle)
{
    int needleSize = strlen(needle);
    int haySize = strlen(haystack);
    if(haySize < needleSize)
        return -1;
    for(int i = 0; i <= haySize - needleSize; i++)
        if(strncmp(haystack+i, needle, needleSize) == 0)
            return i;
    return -1;
}

//AC - 0ms
//KMP - Knuth, Morris and Pratt
int strStr(char* s, char* p)
{
    int size = strlen(p);
    int* next = (int*)malloc(sizeof(int)*size);
    if(size > 0) next[0] = -1;
    int i, j, k;
    for(i=1; i < size; i++)
    {
        next[i] = -1;
        //get the longest 'prefix' that is equal to the suffix;
        for(k = next[i-1]; k >= 0 && p[i] != p[k+1]; k = next[k]);
        if(p[i] == p[k+1]) next[i] = k+1;
    }
    i = 0, j = 0;
    int sSize = strlen(s);
    while(i < sSize && j < size)
    {
        if(s[i] == p[j]) i++, j++;
        else if(j == 0) i++;
        else j = next[j-1]+1;
    }
    if(j == size) return i - j;
    return -1;
}
