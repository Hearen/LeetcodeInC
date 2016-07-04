/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 08:59 CST
Description : Implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
The function prototype should be:
bool isMatch(const char *s, const char *p)
Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

Source      : https://leetcode.com/problems/wildcard-matching/
*******************************************/
class Solution {
public:
    //AC - 20ms - using recorder;
    bool isMatch(string s, string p) 
    {
        int sIndex=0, pIndex=0;
        int sAIndex=-1, pAIndex=-1;
        int sLen=s.length(), pLen=p.length();
        while(sIndex < sLen)
        {
            if(s[sIndex]==p[pIndex] || p[pIndex]=='?') { sIndex++, pIndex++; continue;  }
            if(p[pIndex] == '*') { pAIndex = pIndex++; sAIndex = sIndex; continue;  }
            if(pAIndex > -1) { pIndex = pAIndex+1; sIndex = ++sAIndex; continue;  }
            return false;
        }
        while(p[pIndex] == '*') pIndex++;
        return pIndex==pLen;
    }

    //AC - 28ms - typical DP solution;
    bool isMatch(string s, string p) 
    {
        int sLen = s.length(), pLen = p.length();
        int count = 0;
        for(int i = 0; i < pLen; i++) if(p[i] == '*') count++;
        if((count==0 && pLen!=sLen) || (pLen-count>sLen)) return false;
        int match[sLen+1]{0};
        match[0] = 1;
        for(int i = 0; i < pLen; ++i)
        {
            if(p[i] == '*')
            {
                for(int j = 1; j <= sLen; ++j)
                match[j] = match[j-1] || match[j];
            }
            else
            {
                for(int i = sLen; j > 0; --j)
                    match[j] = match[j-1] && (p[i]=='?' || p[i]==s[j-1]);
                /*int t0, t1 = match[0];*/
                /*for(int j = 1; j <= sLen; ++j)*/
                /*{*/
                    /*t0 = match[j];*/
                    /*match[j] = t1 && (p[i]=='?' || p[i]==s[j-1]);*/
                    /*t1 = t0;*/
                /*}*/
                match[0] = 0;
            }
        }
        return match[sLen];
    }
};
