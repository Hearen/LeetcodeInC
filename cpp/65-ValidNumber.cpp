/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 16 Jun 2016 15:39 CST
Description : Validate if a given string is numeric.
Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
Source      : https://leetcode.com/problems/valid-number/
*******************************************/
class Solution {
public:

    //AC - 8ms - checking the flow just as a pipe;
    bool isNumber(string s) 
    {
        int i = 0;
        bool there_is_e = false;
        bool there_is_dot = false;
        bool there_is_number = false;
        while(s[i] == ' ') i++;
        if(s[i] == '\0') return false; //in case of just white spaces;
        if(s[i]=='+' || s[i]=='-') i++;
        if(s[i] == '.') there_is_dot = true, i++;
        if(!isdigit(s[i])) return false; //digits just closely follow the sign;
        while(isdigit(s[i])) i++; //eat up all the digits;
        if(s[i] == '.') //there can be '.' after integer;
        {
            if(there_is_dot) return false; //but only can appear in the first time;
            i++;
            there_is_dot = true;
        }
        while(isdigit(s[i])) i++; //collect the fraction part after '.';
        if(s[i] == 'e') //consume the 'e';
        {
            i++;
            there_is_e = true;
            there_is_number = false;
            int j = i; 
            while(j<s.length() && !isdigit(s[j])) j++; //there is no number after 'e';
            if(j == s.length()) return false;
            j = i;
            while(j<s.length()) if(s[j++] == '.') return false;//there is no '.' after 'e';
        }
        if(there_is_e && (s[i]=='+' || s[i]=='-')) i++; //only the signs exactly after 'e' can be skipped;
        while(isdigit(s[i])) i++; //ensure the digits after e is digits;
        while(s[i] == ' ') i++;
        return s[i] == '\0';
    }
    //AC - 8ms - beautiful parsing using count;
    bool isNumber(string s) 
    {
        int i = 0, digit_count = 0, dot_count = 0;
        while(s[i] == ' ') i++;
        if(s[i]=='+' || s[i]=='-') i++;
        while(isdigit(s[i]) || s[i]=='.') s[i++]=='.'? dot_count++ : digit_count++;
        if(dot_count>1 || digit_count<1) return false;
        if(s[i] == 'e')
        {
            i++;
            dot_count = digit_count = 0;
            if(s[i]=='+' || s[i]=='-') i++;
            while(isdigit(s[i]) || s[i]=='.') s[i++]=='.'? dot_count++ : digit_count++;
            if(dot_count>0 || digit_count<1) return false;
        }
        while(s[i] == ' ') i++;
        return s[i] == '\0';
    }

    //The function first discards as many whitespace characters (as in isspace) as necessary until the first non-whitespace character is found. Then, starting from this character, takes as many characters as possible that are valid following a syntax resembling that of floating point literals (see below), and interprets them as a numerical value. A pointer to the rest of the string after the last valid character is stored in the object pointed by endptr.
    //AC - 12ms;
    bool isNumber(string s) 
    {
        char *pEnd, *str = (char*)s.c_str();
        while(*str == ' ') str++;
        if(*str == '\0') return false;
        float f = strtof(str, &pEnd);
        while(*pEnd == ' ') pEnd++;
        return *pEnd == '\0';
                                                            
    }

};
