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
#include <stdbool.h>

bool isMatch1(char *s, char* p)
{
    if(*p == '\0') return *s=='\0';
    if(*(p+1) == '*')
        return isMatch(s, p+2) ||  //match zero letter in s;
            ((*s==*p || '.'==*p) && isMatch(++s, p)); //match one or more;
    else
        return *s!='\0' && (*s==*p || '.'==*p) && isMatch(++s, ++p);
}

bool isMatch0(char* s, char* p)
{
    int sLen=strlen(s), pLen=strlen(p);
    int** match=(int**)malloc(sizeof(int*)*(sLen+1));
    for(int i = 0; i < sLen+1; i++)
    {
        match[i] = (int*)malloc(sizeof(int)*(pLen+1));
        memset(match[i], 0, sizeof(int)*(pLen+1));
    }
    match[0][0] = true;
    for(int i = 0; i < sLen+1; i++) //start index should be zero;
    {
        for(int j = 1; j < pLen+1; j++)
        {
            if(p[j-1] != '*')
                match[i][j] = i && match[i-1][j-1] && (p[j-1]=='.' || p[j-1]==s[i-1]);
            else
                match[i][j] = (j>1 && match[i][j-2]) ||  //match zero in s;
                (i && match[i-1][j] && (p[j-2]=='.'||p[j-2]==s[i-1])); //match one or more;
        }
    }
    return match[sLen][pLen];
}

//AC - 4ms;
bool isMatch(char* s, char* p)
{
    int sLen = strlen(s), pLen = strlen(p);
    bool *pre = (bool*)malloc(sizeof(bool)*(pLen+1));
    bool *cur = (bool*)malloc(sizeof(bool)*(pLen+1));
    memset(pre, 0, sizeof(bool)*(pLen+1));
    memset(cur, 0, sizeof(bool)*(pLen+1));
    pre[0] = cur[0] = true;
    for(int i=0; i <= sLen; i++)
    {
        if(i) cur[0]=false; //string is not empty, so pattern cannot be empty;
        for(int j=1; j <= pLen; j++)
        {
            char c=*(p+j-1); //adjust the index for better coding;
            if(c != '*')
                cur[j] = i>0 && pre[j-1] && (c=='.' || c==*(s+i-1));
            else
                //two different situations: match zero or not zero letters in s;
                cur[j] = (j>1 && cur[j-2]) ||  //matching zero;
                    (i>0 && pre[j] && (*(p+j-2)=='.' || *(p+j-2) == *(s+i-1))); //matching one or more - be careful about the index here;
        }
        bool *t = pre; pre = cur, cur = t;
    }
    return pre[pLen];
}
