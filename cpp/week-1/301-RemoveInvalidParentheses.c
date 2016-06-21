/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-05 20:48
Description : Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and  ).
Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]")"
Source      : https://leetcode.com/problems/remove-invalid-parentheses/
*******************************************/
class Solution {
private:
    void traverse(string&s, int pos, string v_s, unordered_set<string>& v, int left, int right, int pair)
    {
        if(s[pos] == '\0') 
        {
            if(!pair) v.insert(v_s);
            return ;
        }
        if(s[pos] == '(')
        {
            if(left) traverse(s, pos+1, v_s, v, left-1, right, pair);
            traverse(s, pos+1, v_s+"(", v, left, right, pair+1);
        }
        else if(s[pos] == ')')
        {
            if(right) traverse(s, pos+1, v_s, v, left, right-1, pair);
            if(pair) traverse(s, pos+1, v_s+")", v, left, right, pair-1);
        }
        else traverse(s, pos+1, v_s+s[pos], v, left, right, pair);
    }
public:
    //AC - 8ms - DFS into different directions;
    vector<string> removeInvalidParentheses(string s) 
    {
        int left=0, right=0, pair=0;
        unordered_set<string> v;
        string v_s;
        for(auto c: s)
        if(c == '(') left++;
        else if(c == ')') left>0? left-- : right++;
        traverse(s, 0, v_s, v, left, right, pair);
        return vector<string>(v.begin(), v.end());
    }
};

