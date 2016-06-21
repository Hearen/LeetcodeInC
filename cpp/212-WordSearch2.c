/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 10:37
Description : Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
For example,
Given words = ["oath","pea","eat","rain"] and board =
[
    ['o','a','a','n'],
    ['e','t','a','e'],
    ['i','h','k','r'],
    ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.
Source      : https://leetcode.com/problems/word-search-ii/
*******************************************/

class Solution {
    class TrieNode
    {
    public:
        bool isWord;
        TrieNode *children[26];
        TrieNode() 
        {
            isWord = false;
            fill_n(children, 26, nullptr);
        }
    };
private:
    const char HOLDER = '#';
    int rowSize, colSize;
    TrieNode* buildTrieTree(const vector<string>& words)
    {
        TrieNode *root = new TrieNode(), *cur = NULL;
        for(const auto& word: words)
        {
            cur = root;
            for(const auto& c: word)
            {
                if(!cur->children[c-'a']) cur->children[c-'a'] = new TrieNode();
                cur = cur->children[c-'a'];
            }
            cur->isWord = true;
        }
        return root;
    }

    void search(vector<vector<char>>& board, int r, int c, TrieNode* root, string& path, vector<string>& v)
    {
        if(r==rowSize || c==colSize || r==-1 || c==-1 || board[r][c]==HOLDER) return ;
        char a = board[r][c];
        root = root->children[a-'a'];
        if(!root) return ; 
        path += a;
        if(root->isWord) v.push_back(path), root->isWord = false; //collecting and set sentinel;
        board[r][c] = HOLDER; //holding position;
        search(board, r-1, c, root, path, v);
        search(board, r+1, c, root, path, v);
        search(board, r, c-1, root, path, v);
        search(board, r, c+1, root, path, v);
        board[r][c] = a; //restore;
        path.pop_back(); //restore;
    }
public:
    //AC - 60ms - quite intuitive solution using TrieTree;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
    {
        vector<string> v;
        string path;
        TrieNode *root = buildTrieTree(words);
        rowSize = board.size();
        if(rowSize == 0) return v;
        colSize = board[0].size();
        for(int r = 0; r < rowSize; ++r)
            for(int c = 0; c < colSize; ++c)
                search(board, r, c, root, path, v);
        return v;
    }

};
