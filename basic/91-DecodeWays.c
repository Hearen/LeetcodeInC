/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 16:35
Description : A message containing letters from A-Z is being encoded to numbers using the following mapping:
'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.
For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
Source      : https://leetcode.com/problems/decode-ways/
*******************************************/
int isValid(char a, char b)
{
    return a=='1' || (a=='2' && b<'7');
}

//AC - 0ms;
int numDecodings0(char* s)
{
    int len = strlen(s);
    if(len == 0 || s[0] == '0') return 0;
    if(len == 1) return 1;
    int t, f1 = 1, f2 = 1;
    for(int i = 1; i < len; i++)
    {
        if(s[i]!='0' && isValid(s[i-1], s[i])) t = f1+f2;
        if(s[i]!='0' && !isValid(s[i-1], s[i])) t = f2;
        if(s[i]=='0' && isValid(s[i-1], s[i])) t = f1;
        if(s[i]=='0' && !isValid(s[i-1], s[i])) return 0;
        f1=f2;
        f2=t;
    }
    return t;
}

int numDecodings(char* s)
{
    int len = strlen(s);
    if(!len || *s=='0') return 0;
    int r1=1, r2=1; //respectively represent r[i-1] and r[i-2];
    for(int i = 0; s[i]; i++)
    {
        if(s[i] == '0') r1 = 0; //cannot be used separately;
        if(s[i-1]=='1' || (s[i-1]=='2' && s[i]<'7'))
        {
            r1 += r2;
            r2 = r1-r2;
        }
        else r2 = r1;
    }
    return r1;
}
