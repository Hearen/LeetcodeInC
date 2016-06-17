/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-10 08:02
Description : Given a list of unique words. Find all pairs of indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
Source      : https://leetcode.com/problems/palindrome-pairs/
*******************************************/
#include <string.h>
#include <vector.h>
class Solution 
{
private:
    bool isPal(string& s, int start, int end)  //start and end refer to index;
    {
        while(s[start] == s[end]) start++, end--;
        return start >= end;
    }

public:
    //AC - 256ms;
    vector<vector<int>> palindromePairs(vector<string>& words) 
    {
        vector<vector<int>> result;
        if(words.empty()) return result;
        unordered_map<string, int> table; //words and its corresponding index;
        for(int i = 0; i < words.size(); i++) table[words[i]]=i;
        for(int i = 0; i < words.size(); i++) 
        {
            string cur = words[i], t_str;
            reverse(cur.begin(), cur.end());
            int t=0, len=cur.size();
            for(int l = 0; l <= len; l++) //l is the length of the sub-string;
            {
                if(isPal(cur,0, l-1))  //the current word will work as prefix;
                {
                    t_str = cur.substr(l);
                    if(table.count(t_str))  //accelerate the checking process;
                    {
                        t = table[t_str];
                        if((t!=i) && (len>=words[t].size())) //avoid duplicates;
                        result.push_back(vector<int>{i, t}); //the matched word will be the suffix;
                    }
                }
                if(isPal(cur, l, len-1)) //the current word will work as suffix;
                {
                    t_str = cur.substr(0,l); 
                    if(table.count(t_str)) 
                    {
                        t = table[t_str];
                        if((t!=i) && (len>words[t].size())) //avoid duplicates;
                        result.push_back(vector<int>{t, i}); //the matched word the prefix;
                    }
                }
            }
        }
        return result;
    }
};
