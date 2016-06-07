/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 13:26
Description : Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
Source      : https://leetcode.com/problems/maximum-product-of-word-lengths/
*******************************************/
#include <string>
#include <vector>
#include <stdlib>
//AC - 40ms - using bit to represent limited 26 different letters;
int maxProduct(char** words, int wSize)
{
    int space = sizeof(int)*wSize; //since we are going to use this value several times, store it;
    int *lens = (int*)malloc(space);
    for(int i = 0; i < wSize; i++) //pre-store the lengths for all words;
        lens[i] = strlen(words[i]);
    int *flags = (int*)malloc(space);
    memset(flags, 0, space);
    for(int i = 0; i < wSize; i++) //retrieve the bit-flag from words;
        for(int j = 0; words[i][j]; j++)
            flags[i] |= 1<<(words[i][j]-'a');
    int max = 0;
    for(int i = 0; i < wSize; i++) //traversing each pair of two different words;
        for(int j = i+1; j < wSize; j++)
            if(!(flags[i] & flags[j])) //using bit flags to check whether there are repeated letter between two words;
            {
                int t = lens[i]*lens[j];
                if(t > max)
                    max = t;
            }
    return max;
}

class Solution {
public:
    int maxProduct(vector<string>& words) 
    {
        vector<int> mask(words.size());
        int result = 0;
        for (int i=0; i<words.size(); ++i)  //reuse the loop;
        {
            for (char c : words[i])
            mask[i] |= 1 << (c - 'a');
            for (int j=0; j<i; ++j)
            if (!(mask[i] & mask[j]))
                    result = max(result, int(words[i].size() * words[j].size()));
        }
        return result;
    }
    int maxProduct(vector<string>& words) 
    {
        unordered_map<int,int> maxlen;
        int result = 0;
        for (string word : words) 
        {
            int mask = 0;
            for (char c : word)
                mask |= 1 << (c - 'a');
            maxlen[mask] = max(maxlen[mask], (int) word.size());
            for (auto maskAndLen : maxlen)
                if (!(mask & maskAndLen.first))
                    result = max(result, (int) word.size() * maskAndLen.second);
        }
        return result;
    }
};
