/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-14 22:15
Description : Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.
For the purpose of this problem, we define empty string as valid palindrome.
Source      : https://leetcode.com/problems/valid-palindrome/
*******************************************/
#include<ctype.h>
#include<stdbool.h>
//AC - 4ms;
bool isPalindrome(char* s)
{
    int size = 0;
    while(*(s+size) != '\0')
        size++;
    int i = 0, j = size - 1;
    while(i <= j)
    {
        while(i <= j && !isalnum(*(s+i)))
            i++;
        while(i <= j && !isalnum(*(s+j)))
            j--;
        if(i <= j && tolower(*(s+i)) != tolower(*(s+j)))
            return false;
        else
        {
            i++;
            j--;
        }
    }
    return true;
}
