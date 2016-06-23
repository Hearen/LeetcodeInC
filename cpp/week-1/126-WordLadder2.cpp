/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-25 19:20
Description : Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,
Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
Source      : https://leetcode.com/problems/word-ladder-ii/
*******************************************/
class Solution 
{
private:
    bool buildTree(unordered_set<string> &forward, unordered_set<string> &backward, unordered_set<string> &dict, unordered_map<string, vector<string> > &tree, bool reversed) 
    {
        if (forward.empty()) return false;
        if (forward.size() > backward.size()) 
            return buildTree(backward, forward, dict, tree, !reversed);
        for (auto &word: forward) dict.erase(word);
        for (auto &word: backward) dict.erase(word);
        unordered_set<string> nextLevel;
        bool done = false; //in case of invalid further searching;
        for (auto &it: forward) //traverse each word in the forward -> the current level of the tree;
        {
            string word = it;
            for (auto &c: word) 
            {
                char c0 = c; //store the original;
                for (c = 'a'; c <= 'z'; ++c) //try each case;
                {
                    if (c != c0) //avoid futile checking;
                    {
                        if (backward.count(word))  //using count is an accelerating method;
                        {
                            done = true;
                            !reversed ? tree[it].push_back(word) : tree[word].push_back(it); //keep the tree generation direction consistent;
                        }
                        else if (!done && dict.count(word)) //since the current level is done the shortest path has already found, needless to further checking next level;
                        {
                            nextLevel.insert(word);
                            !reversed ? tree[it].push_back(word) : tree[word].push_back(it);
                        }
                    }
                }
                c = c0; //restore the word;
            }
        }
        return done || buildTree(nextLevel, backward, dict, tree, reversed);
    }

    void getPath(string &beginWord, string &endWord, unordered_map<string, vector<string> > &tree, vector<string> &path, vector<vector<string> > &paths) //using reference can accelerate;
    {
        if (beginWord == endWord) paths.push_back(path); //till the end;
        else
        {
            for (auto &it: tree[beginWord]) 
            {
                path.push_back(it);
                getPath(it, endWord, tree, path, paths); //DFS retrieving the path;
                path.pop_back();
            }
        }
    }
public:
    vector<vector<string> > findLadders(string beginWord, string endWord, unordered_set<string> &dict) {
        vector<vector<string> > paths;
        vector<string> path(1, beginWord);
        if (beginWord == endWord)  //corner case;
        {
            paths.push_back(path);
            return paths;
        }
        unordered_set<string> forward, backward;
        forward.insert(beginWord);
        backward.insert(endWord);
        unordered_map<string, vector<string> > tree;
        bool reversed = false; //make sure the tree generating direction is consistent, since we have to start from the smaller set to accelerate;
        if (buildTree(forward, backward, dict, tree, reversed))
            getPath(beginWord, endWord, tree, path, paths);
        return paths;
    }
};

