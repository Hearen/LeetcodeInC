/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 20:12 CST
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
class Solution 
{
private:
    bool isMatch(char* s, char* p)
    {
        if(*p == '\0') return *s == '\0';
        if(*(p+1) == '*')
            return isMatch(s, p+2) || (*s!='\0' && (*s==*p || *p=='.') && isMatch(++s, p));
        else 
            return (*s!='\0' && (*s==*p || *p=='.') && isMatch(++s, ++p));
    }
public:
    bool isMatch(string s, string p) 
    {
        char *ss = (char*)s.c_str(), *pp = (char*)p.c_str();
        return isMatch(ss, pp);
    }

	bool isMatch(string s, string p) 
    {
        int sLen = s.length(), pLen = p.length(); 
        int match[pLen+1][sLen+1];
        memset(match, 0, sizeof(int)*(pLen+1)*(sLen+1));
        match[0][0] = 1;
        for(int i = 2; i <= pLen; i += 2)  //for special pattern a*a*a*;
            if(p[i-1] == '*') match[i][0] = 1; else break;
        for(int i = 1; i <= pLen; ++i)
        {
            if(p[i-1] == '*')
            {
				for(int j = 1; j <= sLen; ++j) //zero, one and more;
					match[i][j] = match[i-2][j] || ((p[i-2]==s[j-1] || p[i-2]=='.') && match[i][j-1]);
            }
            else
            {
				for(int j = 1; j <= sLen; ++j)
					match[i][j] = match[i-1][j-1] && (p[i-1]=='.' || p[i-1]==s[j-1]);
            }
        }
        return match[pLen][sLen];
    }
};
