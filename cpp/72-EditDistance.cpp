/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-17 10:08
Description : Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
Source      : https://leetcode.com/problems/edit-distance/
*******************************************/
class Solution {
public:
    //O(n^2) space cost;
	int minDistance(string word1, string word2) 
    {
        int len1 = word1.length(), len2 = word2.length();
        int steps[len1+1][len2+1]{{0}};
        for(int i = 0; i <= len1; ++i) steps[i][0] = i;
        for(int i = 0; i <= len2; ++i) steps[0][i] = i;
        for(int i = 1; i <= len1; ++i)
            for(int j = 1; j <= len2; ++j)
            {
                if(word1[i-1] == word2[j-1]) steps[i][j] = steps[i-1][j-1];
                else steps[i][j] = min(steps[i-1][j], min(steps[i][j-1], steps[i-1][j-1]))+1;
                                    //deleting, inserting and replacing;
            }
        return steps[len1][len2];
    }

    //O(n) space cost;
    int minDistance(string word1, string word2) 
    {
        int len1 = word1.length(), len2 = word2.length(), pre = 0;
        int steps[len2+1]{0};
        for(int i = 0; i <= len2; ++i) steps[i] = i;
        for(int i = 1; i <= len1; ++i)
        {
            pre = i-1; //original states;
            steps[0] = i;
            for(int j = 1; j <= len2; ++j)
            {
                int t = steps[j]; //diagonal state;
                if(word1[i-1] == word2[j-1]) steps[j] = pre;
                else steps[j] = min(steps[j], min(steps[j-1], pre))+1;
                pre = t;
            }
        }
        return steps[len2];
    }
};
