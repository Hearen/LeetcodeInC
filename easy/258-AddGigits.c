/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 16:00
Description : Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
For example:
Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.
Follow up:
Could you do it without any loop/recursion in O(1) runtime?
Source      : https://leetcode.com/problems/add-digits/
*******************************************/
#define LEN 30
char* int2Str(int a, int* size)
{
    char* s = (char*)malloc(sizeof(char)*LEN);
    char t[LEN];
    int index = 0;
    if(a == 0)
        s[index++] = '0';
    while(a)
    {
        t[index++] = a%10 + '0';
        a /= 10;
    }
    for(int i = 0; i < index; i++)
        s[index-i-1] = t[i];
    s[index] = '\0';
    *size = index;
    return s;
}
//AC - 8ms;
//iterative calculation;
int addDigits0(int num)
{
    int len;
    char *s = int2Str(num, &len);
    while(len > 1)
    {
        num = 0;
        while(*s)
          num += *(s++) - '0';
        s = int2Str(num, &len);
    }
    return num;
}

//AC - 4ms - quite weird, the same with the complicated previous solution;
//using formula - the number occur periodically in loop-9 so 
//the result will be either 9 or the result within 9;
int addDigits(int num)
{
    return (num && !(num %= 9))? 9 : num;
}
