/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 11:32
Description : Determine whether an integer is a palindrome. Do this without extra space.
Source      : https://leetcode.com/problems/palindrome-number/
*******************************************/
#include <stdbool.h>
//AC - 56ms;
bool isPalindrome(int n)
{
    if(n < 0) return false; //all negatives are not;
    if(!n && n%10==0) return false; //the leading digit cannot be zero so the last either;
    int t = 0;
    while(t < n) //only half of integer should be checked;
    {
        t = t*10+n%10;
        n /= 10;
    }
    return t==n || t/10==n;
}
