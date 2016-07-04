/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 28 Jun 2016 20:55 CST
Description : Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
Source      : https://leetcode.com/problems/longest-palindromic-substring/
*******************************************/
class Solution {
public:
    string longestPalindrome(string s) 
    {
        int sLen = s.length(), maxLen = 0, maxStart = 0;
        int i = 0, l = 0, r = 0, len = 0;
        while(i<=sLen-maxLen/2)
        {
            l = r = i;
            while(r<sLen-1 && s[r+1]==s[r]) r++;
            i = r+1;
            while(l>0 && r<sLen-1 && s[r+1]==s[l-1]) l--, r++;
            len = r-l+1;
            if(maxLen < len) maxLen = len, maxStart = l;
        }
        return s.substr(maxStart, maxLen);
    }
};
