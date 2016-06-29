/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 20:16
Description : Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.
For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
Source      : https://leetcode.com/problems/palindrome-partitioning-ii/
*******************************************/
class Solution {
public:
    int minCut(string s) 
    {
        int sLen = s.length();
        bool pal[sLen][sLen]; //s[i...j] is palindrome or not;
        memset(pal, 0, sizeof(bool)*sLen*sLen);
        int minCuts[sLen];
        for(int i = sLen-1; i >= 0; --i)
        {
            minCuts[i] = INT_MAX;
            for(int j = i; j < sLen; ++j)
            {
                if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1]))
                {
                    pal[i][j] = 1;
                    if(j == sLen-1) minCuts[i] = 0;
                    else minCuts[i] = min(minCuts[i], minCuts[j+1]+1);
                }
            }
        }
        return minCuts[0];
    }
};
