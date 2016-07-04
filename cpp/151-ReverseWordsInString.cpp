/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Tue, 28 Jun 2016 18:26 CST
Description : Given an input string, reverse the string word by word.
For example,
Given s = "the sky is blue",
return "blue is sky the".
Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.
Source      : https://leetcode.com/problems/reverse-words-in-a-string/
*******************************************/
class Solution {
public:
    //using C++ way;
    void reverseWords(string &s) 
    {
        stringstream ss(s);
        string item;
        ss >> s;
        while(ss >> item) s = item + " " + s;
        if(s.length() && s[0]==' ') s = "";
    }

    //using C way;
	void reverseWords(string &s) 
    {
        string delimiters = " \f\n\r\t\v";
        s.erase(s.find_last_not_of(delimiters)+1); //removing leading white spaces;
        s.erase(0, s.find_first_not_of(delimiters)); //removing trailing white spaces;
        bool flag = false;
        int index, i;
        for(index = 0, i = 0; s[i]; ++i) //only reserve one white space among words;
        {
            if(s[i] != ' ') s[index++] = s[i], flag = false;
            else
            {
                if(!flag) s[index++] = s[i];
                flag = true;
            }
        }
        s.erase(index); //remove left;
        reverse(s.begin(), s.end());
        s += " ";
        int l = 0, r = 0; 
        for(int i = 0; i < s.length(); ++i)
        {
            if(s[i] != ' ') r++;
            else 
            {
                reverse(s.begin()+l, s.begin()+r);
                l = ++r; //move to the beginning of the next word;
            }
        }
        s.erase(s.size()-1);
    }    
};

