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
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        map<string, int> word_count, check_count;
        int sLen = s.length(), dictSize = words.size(), wLen = words[0].size(), i = 0, j = 0;
        vector<int> v;
        string word;
        for(; i < dictSize; ++i) word_count[words[i]]++; //set up a count baseline for checking;
        for(i = 0; i < sLen-dictSize*wLen+1; ++i)
        {
            check_count.clear(); //restart;
            for(j = 0; j < dictSize; ++j) //start from position i and check the following sequence;
            {
                word = s.substr(i+j*wLen, wLen);
                if(word_count.count(word)) { if(check_count[word]++ == word_count[word]) break;  }
                else break;
            }
            if(j == dictSize) v.push_back(i); //all words are covered exactly;
        }
        return v;
    }
};
