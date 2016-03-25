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
//AC - 4ms;
int numDistinct(char* s, char* t)
{
    int sLen = strlen(s), tLen = strlen(t);
    int *pre = (int*)malloc(sizeof(int)*(sLen+1));
    int *cur = (int*)malloc(sizeof(int)*(sLen+1));
    for(int i = 0; i <= sLen; i++)
        pre[i] = 1;
    for(int i = 1; i <= tLen; i++)
    {
        for(int j = 1; j <= sLen; j++)
        {
            if(t[i-1] != s[j-1])
                cur[j] = cur[j-1];
            else
                cur[j] = cur[j-1]+pre[j-1];
        }
        for(int i=0; i <= sLen; i++)
            pre[i] = cur[i];
    }
    return pre[sLen];
}
