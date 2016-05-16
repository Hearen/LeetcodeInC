/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 11:27
Description : Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
Source      : https://leetcode.com/problems/word-pattern/
*******************************************/
#include <stdbool.h>
#include <string.h>
//AC - 0ms;
bool wordPattern(char* pattern, char* str)
{
    const int LEN = 26;
    char** map = (char**)malloc(sizeof(char*)*LEN);
    for(int i = 0; i < LEN; i++)
        map[i] = "";
    char* cur;
    cur = strtok(str, " "); //handle the first substring;
    if(strlen(pattern) == 0 && cur) return false; //corner case;
    map[*pattern-'a'] = cur; //first map;
    while(*pattern++)
    {
        if(*pattern == '\0') break; //ensure the key will be valid;
        int key = *pattern - 'a';
        cur = strtok(NULL, " "); //get next word;
        if(!cur)  return false; //less than pattern;
        if(map[key] == "")
        {
            for(int i = 0; i < LEN; i++) //make sure one letter to just one unique string;
            if(strcmp(map[i], cur) == 0) return false;
            map[key] = cur;
        }
        if(strcmp(map[key], cur) != 0) return false;
    }
    cur = strtok(NULL, " ");//longer than pattern;
    return !cur;
}
