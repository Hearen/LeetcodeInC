/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-16 09:59
Description : Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
For "(()", the longest valid parentheses substring is "()", which has length = 2.
Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
Source      : https://leetcode.com/problems/longest-valid-parentheses/
*******************************************/
class Solution {
public:
    //stack - 8ms;
    int longestValidParentheses(string s) 
    {
        int len = s.length(), longest = 0;
        if(!len) return 0;
        int stack[len]{0}, top = -1;
        stack[++top] = -1;
        for(int i = 0; i < len; ++i)
        {
            int t = stack[top];
            if(t!=-1 && s[i]==')' && s[t]=='(')
                longest = max(longest, i-stack[--top]);
            else stack[++top] = i;
        }
        return longest;
    }

    //DP - 8ms;
	int longestValidParentheses(string s) 
    {
        int len = s.length(), longest = 0;
        if(!len) return 0;
        int t = 0, maxSub[len]{0};
        memset(maxSub, 0, sizeof(int)*len);
        for(int i = 0; i < len; ++i)
        {
            if(s[i] == ')')
            {
                t = i-maxSub[i-1];
                if(t>0 && s[t-1] == '(') maxSub[i] = (t>1? maxSub[t-2] : 0)+maxSub[i-1]+2;
                longest = max(longest, maxSub[i]);
            }
        }
        return longest;
    }
};
