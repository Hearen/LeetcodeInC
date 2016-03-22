/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-21 09:32
Description : Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
If the last word does not exist, return 0.
Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.
Source      : https://leetcode.com/problems/length-of-last-word/
*******************************************/
#include <stdbool.h>
//AC - 0ms;
int lengthOfLastWord(char* s)
{
    int len = 0;
   int in = false; //used to indicate whether in a word or not;
    int pre = 0;
    while(*s)
    {
        if(isalpha(*s))
        {
            len++;
            in = true;
        }
        else
        {
            if(in)
                pre = len;
            in = false;
            len = 0;
        }
        s++;
    }
    if(isalpha(*(s-1))) //the last word includes the last character;
            return len;
    return pre; //the last character is a space;
}
