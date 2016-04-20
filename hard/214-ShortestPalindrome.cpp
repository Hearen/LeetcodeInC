/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-04-20 15:48
Description : Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".
Source      : https://leetcode.com/problems/shortest-palindrome/
Reference   : http://articles.leetcode.com/longest-palindromic-substring-part-ii
*******************************************/
#include <vector.h>
#include <string.h>
class Solution 
{
public:
    //AC - 16ms;
    string shortestPalindromeUsingManacher(string s) 
    {
        string T = "^";
        for(int i = 0; i < s.size(); i++)
            T += "#" + s.substr(i,1);
        T += "#@";
        int n = T.size();
        vector<int> P(n, 0);
        int R = 0, C = 0;
        for(int i = 1; i < n - 1; i++)
        {
            int i_mirr = 2 * C - i;
            P[i] = i < R ? min(P[i_mirr], R - i) : 0;
            while(T[i + P[i] + 1] == T[i - P[i] - 1])
            {
                P[i]++;
                if(i + P[i] > R)
                {
                    C = i;
                    R = i + P[i];
                }
            }
        }
        int maxLen = 0;
        for(int i = 1; i < n - 1; i++)
            if(i - P[i] == 1) maxLen = max(maxLen, P[i]); // only consider palindrome starting from beginning position
        string append = s.substr(maxLen, s.size() - maxLen);
        reverse(append.begin(), append.end());
        return append + s;
    }
    //AC - 8ms;
    string shortestPalindromeUsingKMP(string s) 
    {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s;
        vector<int> p(l.size(), 0);
        for (int i = 1; i < l.size(); i++) 
        {
            int j = p[i - 1];
            while (j > 0 && l[i] != l[j]) j = p[j - 1];
            if(l[i] == l[j]) j++;
            p[i] = j;
        }
        return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
    }
};
