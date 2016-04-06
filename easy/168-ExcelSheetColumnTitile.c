/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 08:45
Description : Given a positive integer, return its corresponding column title as appear in an Excel sheet.
For example:
    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB 
Source      : https://leetcode.com/problems/excel-sheet-column-title/
*******************************************/
//AC - 0ms;
char* convertToTitle(int n)
{
    char* s = (char*)malloc(sizeof(char)*10);
    int index = 0;
    while(n)
    {
        s[index++] = (n-1)%26 + 'A';
        n = (n-1) / 26;
    }
    for(int i = 0; i < index/2; i++)
    {
        char t = s[i];
        s[i] = s[index-i-1];
        s[index-i-1] = t;
    }
    return s;
}
