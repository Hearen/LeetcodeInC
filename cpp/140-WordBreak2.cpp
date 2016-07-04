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
class Solution {
private:
    int sLen, wMaxLen, wMinLen; //using word length range dramatically avoid futile checking;
    void search(string& s, int pos, bool isBreakable[], unordered_set<string>& wordDict, string path, vector<string>& v)
    {
        for(int len = wMinLen; len <= min(wMaxLen, sLen-pos); ++len)
        {
            string t = s.substr(pos, len);
            if(isBreakable[pos+len] && wordDict.count(t))
            {
                if(pos+len == sLen) v.push_back(path+t);
                else search(s, pos+len, isBreakable, wordDict, path+t+" ", v);
            }
        }
    }
public:
    //AC - 4ms - best submission;
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) 
    {
        sLen = s.length();
        for(const auto& word: wordDict)
        {
            wMaxLen = max(wMaxLen, (int)word.length());
            wMinLen = min(wMinLen, (int)word.length());
        }
        bool isBreakable[sLen+1]{false}; //dramatically reduce redundant re-checking;
        isBreakable[sLen] = true;
        for(int i = sLen-wMinLen; i >= 0; --i)
            for(int len = wMinLen; len <= min(wMaxLen, sLen-i); ++len)
                if(isBreakable[i+len] && wordDict.count(s.substr(i, len)))
                    isBreakable[i] = true;
        vector<string> v;
        if(isBreakable[0]) search(s, 0, isBreakable, wordDict, "", v);
        return v;
    }
};
