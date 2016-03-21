/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 09:49
Description : Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
Source      : https://leetcode.com/problems/longest-substring-without-repeating-characters/
*******************************************/
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define LEN 128
int lengthOfLongestSubstring(char* s)
{
    if(s[0] == '\0') return 0;
    int max = 1;
    int map[LEN];
    memset(map, -1, sizeof(int)*LEN);
    for(int i=0, j=0; s[i]; i++)
    {
        int index = s[i];
        if(map[index] > -1) //duplicate;
            j = MAX(map[index]+1, j); //to make duplicate case exactly the same as no-duplicate, add another 1 for adjustment;
        map[index] = i;
        int len = i-j+1; //no duplicate;
        if(len > max)
            max = len;
    }
    return max;
}
