/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-23 15:32
Description : Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".
If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
Source      : https://leetcode.com/problems/minimum-window-substring/
*******************************************/
class Solution {
public:
    //AC - 12ms - best submission;
    string minWindow(string s, string t) 
    {
        int sLen = s.length(), tLen = t.length();
        int char_map[128];
        for(int i = 0; i < 128; ++i) char_map[i] = -sLen; //as a splitter;
        for(int i = 0; i < tLen; ++i) char_map[t[i]] = 0;
        for(int i = 0; i < tLen; ++i) char_map[t[i]]++;
        int l = 0, r = 0, minStart = 0, minLen = INT_MAX; 
        while(r < sLen)
        {
            if(char_map[s[r]]-- > 0) tLen--;
            r++; //move forward again so the window width should be r-l instead of r-l+1;
            while(tLen == 0)//determine left and right boundary of the min window;
            {
                if(r-l < minLen) { minLen = r-l; minStart = l;  }
                if(char_map[s[l++]]++ == 0) tLen++; //get the left boundary;
            }
        }
        return minLen!=INT_MAX? s.substr(minStart, minLen) : ""; //in case of no-such-window case;
    }
};
