/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 28 Jun 2016 09:58 CST
Description : Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".
Source      : https://leetcode.com/problems/shortest-palindrome/
*******************************************/
class Solution {
public:
    string shortestPalindrome(string s) 
    {
        string r_s = s;
        reverse(r_s.begin(), r_s.end());
        string kmp_s = s+"#"+r_s;
        int next[kmp_s.size()]{0};
        next[0] = 0;
        for(int i = 1; i < kmp_s.length(); ++i)
        {
            int j = next[i-1];
            while(j>0 && kmp_s[i]!=kmp_s[j]) j = next[j-1];
            next[i] = j+(kmp_s[i]==kmp_s[j]);
        }
        return r_s.substr(0, r_s.length()-next[kmp_s.size()-1])+s;
    }
};
