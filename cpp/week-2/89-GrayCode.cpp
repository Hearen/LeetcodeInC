/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 21 Jun 2016 16:33 CST
Description : The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2
Source      : https://leetcode.com/problems/gray-code/
*******************************************/
class Solution 
{
public:
    vector<int> grayCode(int n) 
    {
        vector<int> v;
        for(int i = 0, a = 1<<n; i < a; ++i) v.push_back(i^(i>>1));
        return v;
    }
};
