/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-24 11:42
Description : Given a string S and a string T, count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
Source      : https://leetcode.com/problems/distinct-subsequences/
*******************************************/
class Solution {
public:
    //using O(2*n) space;
    int numDistinct(string s, string t) 
    {
        int sLen = s.length(), tLen = t.length();
        vector<int> pre(sLen+1, 1), cur(sLen+1);
        for(int i = 1; i <= tLen; ++i)
        {
            cur[0] = 0;
            for(int j = 1; j <= sLen; ++j)
            {
                if(t[i-1] == s[j-1]) cur[j] = cur[j-1]+pre[j-1]; //select the s[j] or not;
                else cur[j] = cur[j-1]; //cannot set the s[j] here;
            }
            cur.swap(pre);
        }
        return pre[sLen];
    }

    //using just O(n) space;
	int numDistinct(string s, string t) 
    {
        int sLen = s.length(), tLen = t.length();
        int cur[tLen+1]{0};
        cur[0] = 1;
        for(int i = 1; i <= sLen; ++i)
            for(int j = tLen; j > 0; --j)
                if(t[j-1] == s[i-1]) cur[j] += cur[j-1];
        return cur[tLen];
    }
};
