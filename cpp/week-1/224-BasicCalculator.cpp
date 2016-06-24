/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 19:42 CST
Description : Implement a basic calculator to evaluate a simple expression string.
The expression string may contain open ( and closing parentheses  ), the plus + or minus sign -, non-negative integers and empty spaces .
You may assume that the given expression is always valid.
Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
Source      : https://leetcode.com/problems/basic-calculator/
*******************************************/
class Solution {
private:
    int calculate(string& s, int& pos) //using reference to globally use the index;
    {
        int sum = 0, sign = 1;
        while(pos<s.length() && s[pos]!=')') //ensure the parentheses will be properly calculated;
        {
            if(s[pos]=='+' || s[pos]==' ') { pos++; sign = 1; } //handle the plus operator and preceding white spaces at the same time;
            else if(s[pos] == '-') { pos++; sign = -1; }
            else if(s[pos] == '(') { pos++; sum += sign*calculate(s, pos); } //calculate the parentheses;
            else
            {
                int num = 0;
                while(isdigit(s[pos])) num = 10*num + s[pos++]-'0';
                sum += sign*num; 
            }
        }
        pos++; //skip the close parentheses;
        return sum;
    }
public:
    //AC - 20ms - second best submission - intuitive recursive method;
    int calculate(string s) 
    {
        int pos = 0;
        return calculate(s, pos);
    }

    //AC - 16ms - iterative solution using stack to record previous result;
    int calculate(string s) 
    {
        stack<int> sums, signs;
        int sum = 0, sign = 1, num = 0;
        for(char c: s)
        {
            if(isdigit(c)) num = 10*num + c - '0';
            else 
            {
                sum += sign*num;
                num = 0;
                if(c == '+' || c == ' ') sign = 1; 
                else if(c == '-') sign = -1;
                else if(c == '(') { sums.push(sum), signs.push(sign); sum = 0, sign = 1;  }
                else if(c == ')') { sum = signs.top()*sum + sums.top(); signs.pop(), sums.pop();  }
            }
        }
        return sum + sign*num;
    }
};
