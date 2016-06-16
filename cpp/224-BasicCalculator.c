/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-29 14:41
Description : 
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

    //AC - 16ms - iterative solution using stack to record precedented result;
    int calculate(string s) 
    {
        stack<int> sums, signs;
        int sum = 0, sign = 1, num = 0, i = 0;
        for(char c: s)
        {
            if(isdigit(c)) num = 10*num + c - '0';
            else 
            {
                sum += sign*num;
                num = 0;
                if(c == '+' || c == ' ') sign = 1, i++; 
                else if(c == '-') sign = -1, i++;
                else if(c == '(') { sums.push(sum), signs.push(sign); sum = 0, sign = 1, i++;  }
                else if(c == ')') { sum = signs.top()*sum + sums.top(); signs.pop(), sums.pop(), i++;  }
            }
        }
        return sum + sign*num;
    }
};
