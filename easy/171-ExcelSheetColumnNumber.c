/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 08:24
Description : Given a column title as appear in an Excel sheet, return its corresponding column number.
For example:
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
Source      : https://leetcode.com/problems/excel-sheet-column-number/
*******************************************/
//AC - 4ms;
int titleToNumber(char* s)
{
    int sum = 0;
    while(*s) sum = 26*sum+(*(s++)-'A'+1);
    return sum;
}
