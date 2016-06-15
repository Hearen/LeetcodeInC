/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 15 Jun 2016 16:33 CST
Description : Given two numbers represented as strings, return multiplication of the numbers as a string.
Note:
The numbers can be arbitrarily large and are non-negative.
Converting the input string to integer is NOT allowed.
You should NOT use internal library such as BigInteger.
Source      : https://leetcode.com/problems/multiply-strings/
*******************************************/
class Solution {
public:
    //AC - 8ms - careful about the corner cases;
    string multiply(string num1, string num2) 
    {
        string s;
        vector<int> v(num1.size()+num2.size()-1, 0);
        for(int i = num1.size()-1; i >= 0; --i)
        for(int j = num2.size()-1; j >= 0; --j)
        v[i+j] += (num1[i]-'0') * (num2[j]-'0');
        for(int i = v.size()-1; i > 0; --i)
        {
            v[i-1] += v[i] / 10;
            v[i] %= 10;
        }
        if(v[0] == 0) return "0"; //started with '0', it must be zero;
        if(v[0] / 10) //there is still a carrier to be collected;
        {
            s += to_string(v[0]/10);
            v[0] %= 10;
        }
        for(int i = 0; i < v.size(); ++i) s += to_string(v[i]);
        return s;
    }
};
