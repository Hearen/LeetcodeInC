/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-14 16:09
Description : Implement regular expression matching with support for '.' and '*'.
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
The function prototype should be:
bool isMatch(const char *s, const char *p)
Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
Source      : https://leetcode.com/problems/regular-expression-matching/
*******************************************/
class Solution {
private:
    bool isMatch(char* s, char* p)
    {
        if(*p == '\0') return *s == '\0';
        if(*(p+1) == '*')
        return isMatch(s, p+2) || (*s!='\0' && (*s==*p || *p=='.') && isMatch(++s, p));
        else return (*s!='\0' && (*s==*p || *p=='.') && isMatch(++s, ++p));
    }
public:
    // We define the state P[i][j] to be true if s[0..i) matches p[0..j) and false otherwise. Then the state equations are:
    //
    // P[i][j] = P[i - 1][j - 1], if p[j - 1] != '*' && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
    // P[i][j] = P[i][j - 2], if p[j - 1] == '*' and the pattern repeats for 0 times;
    // P[i][j] = P[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'), if p[j - 1] == '*' and the pattern repeats for at least 1 times.]]
    //AC - 4ms - DP classic solution;
    bool isMatch(string s, string p) 
    {
        int sLen = s.length(), pLen = p.length(); 
        bool dp[sLen+1][pLen+1]{{false}};
        dp[0][0] = true;
        for (int i = 0; i <= sLen; i++)
            for (int j = 1; j <= pLen; j++)
                if (p[j - 1] == '*') 
                    dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                else dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
        return dp[sLen][pLen];
    }

    //AC - 28ms - recursive method;
    bool isMatch(string s, string p) 
    {
        char *ss = (char*)s.c_str(), *pp = (char*)p.c_str();
        return isMatch(ss, pp);
    }
};
