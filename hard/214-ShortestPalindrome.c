/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-18 11:09
Description : 
Source      : https://leetcode.com/problems/shortest-palindrome/
*******************************************/
#include <stdlib.h>
//AC - 0ms - KMP;
//http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
char* shortestPalindrome(char* s) 
{
    if (!s || !*s) return strdup("");
    const int N = strlen(s);
    const int HN = (N >> 1);
    int next[HN], k, i, ch;

    //get the array of the longest length that the prefix matches the suffix;
    k = next[0] = 0;
    for (i = 1; i < HN; i++) 
    {
        ch = s[i]; //record the current character;
        while ((k > 0) && (ch != s[k])) k = next[k - 1]; //searching the longest suffix matching the prefix;
        if (ch == s[k]) k++;
        next[i] = k;
    }

    //using the array next to search reversely;
    for (i = N - 1, k = 0; i >= k; i--) 
    {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = next[k - 1];
        if (ch == s[k]) k++; //the length that matches;
    }

    // Finally, only (N - i - k - 1) chars need to be added to make the shortest palindrome
    int len = N - (i + k);
    char* ret = (char*)malloc((len + N)* sizeof(char));
    if (ret != NULL) 
    {
        char* p = ret;
        for (i = N - 1; i > N - len; i--) *p++ = s[i];
        strcpy(p, s);
    }
    return ret;
}
