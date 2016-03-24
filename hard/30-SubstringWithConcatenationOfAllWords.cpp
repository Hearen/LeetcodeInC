/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 10:44
Description : You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
Source      : https://leetcode.com/problems/substring-with-concatenation-of-all-words/
*******************************************/
#include <vector.h>
class Solution {
    public:
        vector<int> findSubstring(string s, vector<string>& words) 
        {
            unordered_map<string, int> counts;
            for (string word : words) counts[word]++;
            int n = s.length(), num = words.size(), len = words[0].length();
            vector<int> indexes;
            for (int i = 0; i < n - num * len + 1; i++) 
            {
                unordered_map<string, int> seen;
                int j = 0;
                for (; j < num; j++) 
                {
                    string word = s.substr(i + j * len, len);
                    if (counts.find(word) != counts.end()) 
                    {
                        if (seen[word]++ >= counts[word]) break;
                    }
                    else break;
                }
                if (j == num) indexes.push_back(i);
            }
            return indexes;
        }
};
