/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-24 16:04
Description : Given an array of strings, group anagrams together.
For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]
Note:
For the return value, each inner list's elements must follow the lexicographic order.
All inputs will be in lower-case.
Source      : https://leetcode.com/problems/anagrams/
*******************************************/
#include <vector.h>
//using multiset<string> to auto-sort strings inserted;
//using count sort instead of built-in sort to accelerate;
class Solution {
    public:
        //AC - 60ms;
        vector<vector<string>> groupAnagrams0(vector<string>& strs) 
        {
            unordered_map<string, vector<string>> map;
            for(auto &v: strs)
            {
                string t(v);
                sort(t.begin(), t.end());
                map[t].push_back(v);
            }
            vector<vector<string>> result(map.size());
            int k = 0;
            for(auto iter = map.begin(); iter != map.end(); ++iter, ++k)
            {
                result[k].swap(iter->second);
                sort(result[k].begin(), result[k].end());
            }
            return result;
        }
        
        //AC - 76ms;
        vector<vector<string>> groupAnagrams(vector<string>& strs) 
        {
            vector<vector<string>> result;
            unordered_map<string, multiset<string>> dict;
            for(auto str : strs)
            {
                string t = str;
                //sort(t.begin(), t.end());
                t = countSort(t);
                dict[t].insert(str);
            }
            for(auto a : dict)
            {
                vector<string> temp(a.second.begin(), a.second.end());
                result.push_back(temp);
            }
            return result;
        }

        /** use the count sort to accelerate the sorting process **/
        string countSort(string &s)
        {
            vector<int> c(26, 0);
            int n=s.size();
            for(int i=0; i<n; i++)  c[s[i]-'a']++;
            int p=0;
            string t(n, 'a');
            for(int j=0; j<26; j++)
            {
                for(int i=0; i<c[j]; i++)
                    t[p++]+=j;
            }
            return t;
        }
};
