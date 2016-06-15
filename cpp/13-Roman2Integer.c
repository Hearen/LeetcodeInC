/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-21 08:56
Description : Given a roman numeral, convert it to an integer.
Input is guaranteed to be within the range from 1 to 3999.
Source      : https://leetcode.com/problems/roman-to-integer/
*******************************************/
#include<string.h>
//Roman numeral
//any of the letters representing numbers in the Roman numerical system: I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1,000. In this system a letter placed after another of greater value adds (thus XVI or xvi is 16), whereas a letter placed before another of greater value subtracts (thus XC is 90).

class Solution 
{
public:
    //AC - 60ms - from left to right using unordered_map;
    int romanToInt(string s) 
    {
        unordered_map<char, int> roman_map { { 'I' , 1  },{ 'V' , 5  },{ 'X' , 10  }, 
            { 'L' , 50  }, { 'C' , 100  }, { 'D' , 500  }, { 'M' , 1000  }  };
        int pre = 1, cur = 1, sum = 0;
        for(int i = s.length()-1; i >= 0; --i)
        {
            cur = roman_map[s[i]];
            if(cur < pre) sum -= cur;
            else sum += cur, pre = cur;
        }
        return sum;
    }


    //AC - 36ms - from right to left and using array to accelerate searching;
    int romanToInt(string s) 
    {
        if (s.empty()) return 0;
        int roman_map[24] = {};
        roman_map['I' - 'A'] = 1;
        roman_map['V' - 'A'] = 5;
        roman_map['X' - 'A'] = 10;
        roman_map['L' - 'A'] = 50;
        roman_map['C' - 'A'] = 100;
        roman_map['D' - 'A'] = 500;
        roman_map['M' - 'A'] = 1000;

        auto sum = 0;
        auto right = roman_map[s.front() - 'A'];
        for (int i = 1; i < s.size(); ++i) 
        {
            auto curr = right;
            right = roman_map[s[i] - 'A'];
            if (right > curr) sum -= curr;
            else sum += curr;
        }
        return sum + right;
    }

};
