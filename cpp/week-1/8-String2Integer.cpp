/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 15 Jun 2016 15:33 CST
Description : Implement atoi to convert a string to an integer.
Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
Source      : https://leetcode.com/problems/string-to-integer-atoi/
*******************************************/
class Solution {
public:
    //AC - 8ms - using dumb direct method;
    int myAtoi(string str) 
    {
        int i = 0;
        int sign = 1;
        long num = 0;
        while(isspace(str[i])) i++;
        if(str[i]=='-' || str[i]=='+')
            if(str[i++] == '-') sign *= -1;
        while(str[i]=='0') i++;
        while(isdigit(str[i]))
        {
            num = 10*num + str[i++]-'0';
            if(num > fabs(long(INT_MIN))) break;
        }
        num *= sign;
        if(num < INT_MIN) return INT_MIN;
        if(num > INT_MAX) return INT_MAX;
        return num;
    }

    //AC - 12ms - using built-in methods;
    int myAtoi(string str)
    {
        int out = 0;
        stringstream ss(str);
        ss >> out;
        return out;
    }
};
