/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 29 Jun 2016 08:28 CST
Description : Implement strStr().
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
Source      : https://leetcode.com/problems/implement-strstr/
*******************************************/
class Solution {
public:
    int strStr(string haystack, string needle) 
    {
        int nLen = needle.length(), hLen = haystack.length();
        if(nLen == 0) return 0;
        int next[nLen]{0};
        next[0] = 0;
        for(int i = 1; i < nLen; ++i)
        {
            int j = next[i-1];
            while(j>0 && needle[i]!=needle[j]) j = next[j-1];
            next[i] += j+(needle[i]==needle[j]); //the length of the matched prefix;
        }
        int i = 0, j = 0;
        while(i < hLen)
        {
            while(haystack[i]!=needle[j] && j>0) j = next[j-1];
            if(haystack[i] == needle[j]) j++;
            if(j == nLen) return i-j+1;
            i++;
        }
        return -1;
    }
};

