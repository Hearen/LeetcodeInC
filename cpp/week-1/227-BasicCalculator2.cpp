/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-10 14:01
Description : Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
You may assume that the given expression is always valid.
Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Source      : https://leetcode.com/problems/basic-calculator-ii/
*******************************************/
#include <cstdbool.h>
int calculate0(char* s)
{
    bool d = false;
    int len = strlen(s); 
    int ret=0, sign=1, num=0, pre=0;
    for(int i = 0; i < len+1; i++)
    {
        if(isdigit(s[i]))
            num = 10*num+s[i]-'0';
        else if(' ' != s[i])
        {
            if(d) //update the current number since the previous operator is '/';
            {
                num = pre/num;
                d = !d; //reset d flag;
            }
            if(s[i] == '/') 
            {
                d = true; //set d flag;
                pre = num*sign; //update previous number;
                sign = 1; //reset sign to its default value;
            }
            else if(s[i] == '*') //store the current number to sign;
                sign *= num;
            else
            {
                ret += sign*num; //collect the result before previous operator;
                sign = (s[i]=='+')? 1 : -1; //reset sign ignoring the last character since we've done with it already;
            }
            num = 0; //reset number for next collecting;
        }
    }
    return ret;
}

class Solution {
public:
    int calculate(string s) 
    {
        stack<int> nums;
        char sign = '+';
        int sum = 0, num = 0;;
        for(int i = 0; i < s.length()+1; ++i)
        {
            if(isdigit(s[i])) num = 10*num+s[i]-'0';
            else if(s[i] != ' ')
            {
                if(sign == '+') nums.push(num);
                else if(sign == '-') nums.push(-num);
                else if(sign == '*') { num *= nums.top(); nums.pop(); nums.push(num);  }
                else if(sign == '/') { num = nums.top()/num; nums.pop(); nums.push(num);  }
                sign = s[i];
                num = 0;
            }
        }
        while(!nums.empty())
        {
            sum += nums.top();
            nums.pop();
        }
        return sum;
    }

    //AC - 16ms - efficient parser;
    int calculate(string s) 
    {
        bool d = false;
        int sum = 0, num = 0, pre = 0, sign = 1;
        for(int i = 0; i < s.length()+1; ++i)
        {
            if(isdigit(s[i])) num = 10*num+s[i]-'0';
            else if(s[i] != ' ')
            {
                if(d)
                {
                    num = pre/num;
                    d = false;
                }
                if(s[i] == '/')
                {
                    d = true;
                    pre = sign*num;
                    sign = 1;
                }
                else if(s[i] == '*')
                    sign *= num;
                else
                {
                    sum += sign*num;
                    sign = s[i]=='+'? 1 : -1;
                }
                num = 0;
            }
        }
        return sum;
    }
};
