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
#include <stdbool.h>
#include <stdlib.h>
//AC - 0ms - using counter to ensure including each letter
//using visited to accelerate the checking process;
char* removeDuplicateLetters0(char* s)
{
    int count[26] = {0};
    bool visited[26] = {0};
    int len = strlen(s);
    for(int i = 0; i < len ;i++) count[s[i]-'a']++; //count the frequency of each character;
    char *t = (char*)malloc(sizeof(char)*27); //used to store the result string;
    int size = 0; //used to indicate the length of the result string;
    for(int i = 0; i < len; i++)
    {
        int index = s[i]-'a';
        count[index]--;
        if(visited[index]) continue; //stored already, needless to check the result string;
        int j = size-1; //not visited before, check it in the result string;
        for(; j > -1; j--)
        {
            int index = t[j]-'a';
            if(s[i] < t[j] && count[index]) visited[index] = false; //if the character t[j] is bigger and there is still such character in the remaining substring, to keep lexicographical order, we have to remove it from the result string and meantime reset visited records;
            else break;
        }
        size = j+1; //update the size of the result string;
        t[size++] = s[i];
        visited[index] = true;
    }
    t[size] = '\0';
    return t;
}

//selecting the valid smallest, remove the invalid
//and then select the next smallest valid;
void helper(char* s, char* t, int* returnSize)
{
    int len = strlen(s);
    if(!len) return ;
    int count[26] = {0};
    int index = 0;
    for(int i = 0; i < len; i++) count[s[i]-'a']++;
    for(int i = 0; i < len; i++)
    {
        if(s[i] < s[index]) //search for the smallest;
            index = i;
        if(!(--count[s[i]-'a'])) //ensure every letter appears at least once, do not exclude any letter;
            break;
    }
    char c = s[index];
    *returnSize += 1;
    t[*returnSize-1] = c;
    int newIndex = 0;
    for(int i = index+1; i < len; i++) //reconstructing the left substring by removing the collected character and the letters before the selected since they are invalid after selecting the letter in 'index' position;
        if(s[i] != c)
            s[newIndex++] = s[i];
    s[newIndex] = '\0';
    helper(s, t, returnSize);
}

//AC - 4ms - quite intuitive solution selecting the smallest one by one;
char* removeDuplicateLetters(char* s)
{
    char* t = (char*)malloc(sizeof(char)*27);
    int size = 0;
    helper(s, t, &size);
    t[size] = '\0';
    return t;
}
