/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-25 16:18
Description : Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,
Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
Source      : https://leetcode.com/problems/word-ladder/
*******************************************/
#include <string>
#include <unordered_set.h>
using namespace std;
class Solution
{
    public:
        //AC - 59ms;
        int ladderLength(string bWord, string eWord, unordered_set<string>& wordList)
        {
            if(bWord == eWord) return 1;
            unordered_set<string> bList, eList;
            bList.insert(bWord);
            eList.insert(eWord);
            wordList.erase(bWord);
            wordList.erase(eWord);
            int len = 1;
            while(!bList.empty()&&!eList.empty())
            {
                if(bList.size() > eList.size()) bList.swap(eList);
                unordered_set<string> tmpList;
                for(auto cur: bList) //access by value, it will be copied;
                {
                    for(auto &c: cur) //access by reference, it will be directly accessed;
                    {
                        char c0 = c;
                        for(c = 'a'; c <= 'z'; c++)
                        {
                            if(c != c0) //avoid invalid further checking;
                            {
                                if(eList.count(cur)) return len+1;
                                if(wordList.count(cur)) //build up intermediate set and removing noise;
                                {
                                    tmpList.insert(cur);
                                    wordList.erase(cur);
                                }
                            }
                        }
                        c = c0;
                    }
                }
                bList.swap(tmpList); //update bList;
                len++;
            }
            return 0;
        }
};
