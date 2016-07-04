/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Fri, 24 Jun 2016 21:13 CST
Description : You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]
You should return the indices: [0,9].
(order does not matter).
Source      : https://leetcode.com/problems/substring-with-concatenation-of-all-words/
*******************************************/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        unordered_map<string, int> word_count, check_count;
        vector<int> v;
        int wLen = words[0].length(), size = words.size(), sLen = s.length();
        for(auto &w: words) word_count[w]++;
        for(int i = 0; i <= sLen-size*wLen; ++i)
        {
            check_count.clear();
            int j = 0;
            for(; j < size; ++j)
            {
                string word = s.substr(i+j*wLen, wLen);
                if(word_count.count(word)) {if(check_count[word]++ == word_count[word]) break;}
                else break;
            }   
            if(j == size) v.push_back(i);
        }
        return v;
    }
};
