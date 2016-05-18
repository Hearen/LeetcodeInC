/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-12 09:01
Description : Given two strings s and t, write a function to determine if t is an anagram of s.
For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.
Note:
You may assume the string contains only lowercase alphabets.
Source      : https://leetcode.com/problems/valid-anagram/
*******************************************/
#include <stdbool.h>

//AC - 0ms;
#define LEN 26
bool isAnagram(char* s, char* t)
{
    if(strlen(s) != strlen(t)) return false;
    int counter[LEN] = {0};
    while(*s) counter[*s++-'a']++;
    while(*t)
        if(counter[*t++-'a']-- < 1) return false;
    return true;
}
