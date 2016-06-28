/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 28 Jun 2016 11:15 CST
Description : Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
Source      : https://leetcode.com/problems/interleaving-string/
Reference   : https://leetcode.com/discuss/19973/8ms-c-solution-using-bfs-with-explanation
*******************************************/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) 
    {
        int len1 = s1.length(), len2 = s2.length(), len3 = s3.length(), i3 = 0;
        if(len1+len2 != len3) return false;
        if(len3 == 0) return true;
        int pre[len2+1]{0}, cur[len2+1]{0}, i = 0;
        pre[0] = 1;
        while(s2[i] == s3[i]) pre[++i] = 1;
        for(int i = 1; i <= len1; ++i)
        {
            for(int j = 0; j <= len2; ++j)
                cur[j] = (j>0 && cur[j-1] && s2[j-1]==s3[i+j-1]) ||
                    (pre[j] && s1[i-1]==s3[i+j-1]);
            memcpy(pre, cur, sizeof(int)*(len2+1));
        }
        return pre[len2];
    }
};
