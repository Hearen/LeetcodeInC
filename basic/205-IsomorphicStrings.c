/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-13 08:18
Description : Given two strings s and t, determine if they are isomorphic.
Two strings are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.
Given "foo", "bar", return false.
Given "paper", "title", return true.
Source      : https://leetcode.com/problems/isomorphic-strings/
*******************************************/
#include <stdbool.h>
//AC - 0ms - ensure one to one distinctive;
bool isIsomorphic0(char* s, char* t)
{
    char map[128] = {0};
    while(*s != '\0')
    {
        if(map[*s]==0)
        {
            map[*s] = *t;
            int count = 0;
            for(int i = 0; i < 128; i++)
                if(map[i] == *t)
                    count++;
            if(count > 1)
                return false;
        }
        else if(map[*s] != *t)
            return false;
        s++, t++;
    }
    return true;
}

//AC - 0ms;
bool isIsomorphic(char* s, char* t)
{
    char ss[128]={0}, tt[128]={0};
    while(*s)
    {
        char a=*s++, b=*t++;
        if(ss[a]==0 && tt[b]==0)
        {
            ss[a] = b;
            tt[b] = a;
            continue;
        }
        if(ss[a]!=b || tt[b]!=a) return false;
    }
    return true;
}
