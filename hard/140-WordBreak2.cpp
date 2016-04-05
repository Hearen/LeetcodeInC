/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-17 16:49
Description : Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.
For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].
Source      : https://leetcode.com/problems/word-break-ii/
*******************************************/
#include <string.h>
#include <vector.h>
class Solution {
private: //DFS path build function
    void buildPath(bool isBreakable[], string &s, int startIndex, vector<string> &res, string sub, unordered_set<string>& wordDict, int minlen, int maxlen)
    {
        int i, len = s.size(); //i is the length of the substring;
        for(i =minlen; i<= min(maxlen, len - startIndex); ++i)
        {
            if(isBreakable[startIndex+i] && wordDict.count(s.substr(startIndex,i))) 
            {
                if(startIndex+i == len) res.push_back(sub + s.substr(startIndex,i));
                else buildPath(isBreakable, s, startIndex+i, res, sub + s.substr(startIndex,i) + " ", wordDict, minlen, maxlen);
            }
        }
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) 
    {
        int sSize = s.size(), len, i, minlen = INT_MAX, maxlen = INT_MIN;
        vector<string> res;
        bool isBreakable[sSize+1];
        fill_n(isBreakable, sSize+1, false);
        // find the minimum and maximum word length to accelerate the searching process;
        for (string word : wordDict) 
        { 
            minlen = min(minlen, (int)word.length());
            maxlen = max(maxlen, (int)word.length()); 
        }        
        //DP to build isBreakable
        for(i=sSize-minlen, isBreakable[sSize]= true; i>=0; --i)
        {
            for(len=minlen; len<=min(maxlen, sSize-i); ++len)
            {
                if(isBreakable[i+len] && wordDict.count(s.substr(i,len)) ) 
                {
                    isBreakable[i] = true; break;
                }
            }
        }
        //if breakable, do DFS path building
        if(isBreakable[0]) buildPath(isBreakable, s, 0, res, "", wordDict, minlen, maxlen);
        return res;
    }
};

