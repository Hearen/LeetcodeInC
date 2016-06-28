/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 28 Jun 2016 14:32 CST
Description : Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

great
/    \
gr    eat
/ \    /  \
g   r  e   at
            / \
            a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

rgeat
/    \
rg    eat
/ \    /  \
r   g  e   at
            / \
            a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

rgtae
/    \
rg    tae
/ \    /  \
r   g  ta  e
        / \
        t   a
We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
Source      : https://leetcode.com/problems/scramble-string/
*******************************************/
class Solution {
private:
    int count[256];
    bool isnScramble(const char* s1, const char* s2, int len)
    {
        if(!strncmp(s1, s2, len)) return true;
        memset(count, 0, sizeof(int)*256);
        for(int i = 0; i < len; ++i) count[s1[i]]++, count[s2[i]]--;
        for(int i = 0; i < 256; ++i) if(count[i]) return false;
        for(int i = 1; i < len; ++i)
            if((isnScramble(s1, s2, i)&&isnScramble(s1+i, s2+i, len-i)) ||
                (isnScramble(s1+len-i, s2, i)&&isnScramble(s1, s2+i, len-i))) return true;
        return false;
    }
public:
    //recursive method pruning in a smart way;
    bool isScramble(string s1, string s2) 
	{
        return isnScramble(s1.c_str(), s2.c_str(), s1.length());
    }
	
    //complicated DP but interesting;
	bool isScramble(string s1, string s2) 
    {
        int len = s1.length(), i = 0, j = 0, k = 0;
        if(!len) return true;
        int match[len+1][len][len]{{{0}}};
        for(i = 0; i < len; ++i)
            for(j = 0; j < len; ++j)
                match[1][i][j] = (s1[i]==s2[j]);
        for(int size = 2; size <= len; ++size)
            for(i = 0; i <= len-size; ++i)
                for(j = 0; j <= len-size; ++j)
                    for(k = 1; k<size&&!match[size][i][j]; ++k)
                        match[size][i][j] = (match[k][i][j]&&match[size-k][i+k][j+k]) ||
                                    (match[k][i+size-k][j]&&match[size-k][i][j+k]);
        return match[len][0][0];
    }
};
