/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-22 10:41
Description : Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
Example:
Given "bcabc"
Return "abc"
Given "cbacdcbc"
Return "acdb"
Source      : https://leetcode.com/problems/remove-duplicate-letters/
*******************************************/
class Solution {
public:
    //AC - 4ms - intuitive method checking one by one till the end;
    string removeDuplicateLetters(string s) 
    {
        int char_count[26]{0}; //ensure all letters are covered;
        bool visited[26]{false}; //avoid duplicates and meantime accelerate the checking;
        char t[27]; //collector used to collect the letters;
        int size = 0;
        for(int i = 0; s[i]; ++i) char_count[s[i]-'a']++;
        for(int i = 0; s[i]; ++i)
        {
            char_count[s[i]-'a']--;
            if(visited[s[i]-'a']) continue;
            int j = size-1;
            for(; j >= 0; --j) //use un-visited letters to update the collector t;
            {
                if(s[i]>t[j] || !char_count[t[j]-'a']) break; //s[i] is bigger or there is no t[j] in the following substring any more then we should place s[i] just after t[j];
                else visited[t[j]-'a'] = false; //delete from collector t;
            }
            t[++j] = s[i]; //insert to the right position;
            visited[s[i]-'a'] = true; //label s[i] as visited;
            size = j+1; //update the size of collector t;
        }
        t[size] = '\0'; //terminate the collector;
        return t;
    }
};
