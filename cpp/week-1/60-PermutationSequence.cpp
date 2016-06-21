/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 15 Jun 2016 20:52 CST
Description : The set [1,2,3,…,n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
Note: Given n will be between 1 and 9 inclusive.
Source      : https://leetcode.com/problems/permutation-sequence/
*******************************************/
class Solution {
public:
    //TLE - its efficiency is too bad, though it works.
    string getPermutation(int n, int k) 
    {
        vector<int> v;
        for(int i = 1; i <= n; i++) v.push_back(i);
        while(k > 1)
        {
            int i = n-2, j = n-1;
            while(v[i] > v[i+1]) i--;
            while(v[i] > v[j]) j--;
            swap(v[i], v[j]);
            reverse(v.begin()+i+1, v.end());
            k--;
        }
        string s;
        for(int i = 0; i < n; i++) s += to_string(v[i]);
        return s;
    }

    //AC - 0ms - using combination and permutation logics - very terse;
    string getPermutation(int n, int k) 
    {
        int i = 1, j = 0, p = 1;
        string s;
        for(; i <= n; ++i)
        {
            p *= i; //n!;
            s += char('0'+i); //generate the sequence string as "123...n";
        }
        for(i = 0, k--; i < n; ++i)
        {
            p /= n-i; //(n-i)!;
            j = i + k/p; //get character for current position i;
            char c = s[j];
            for(; j > i; --j) s[j] = s[j-1]; //shift to the right for one position;
            s[i] = c;
            k %= p; //consider the left sequence;
        }
        return s;
    }
};
