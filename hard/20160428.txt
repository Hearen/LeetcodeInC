/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-25 19:20
Description : Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,
Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
Source      : https://leetcode.com/problems/word-ladder-ii/
*******************************************/
#include <vector.h>
class Solution 
{
    public:
        vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &dict) {
            vector<vector<string> > paths;
            vector<string> path(1, beginWord);
            if (beginWord == endWord)  //corner case;
            {
                paths.push_back(path);
                return paths;
            }
            unordered_set<string> forward, backward;
            forward.insert(beginWord);
            backward.insert(endWord);
            unordered_map<string, vector<string> > tree;
            bool reversed = false; //make sure the tree generating direction is consistent, since we have to start from the smaller set to accelerate;
            if (buildTree(forward, backward, dict, tree, reversed))
                getPath(beginWord, endWord, tree, path, paths);
            return paths;
        }
    private:
        bool buildTree(unordered_set<string> &forward, unordered_set<string> &backward, unordered_set<string> &dict, unordered_map<string, vector<string> > &tree, bool reversed) 
        {
            if (forward.empty()) return false;
            if (forward.size() > backward.size()) 
                return buildTree(backward, forward, dict, tree, !reversed);
            for (auto &word: forward) dict.erase(word);
            for (auto &word: backward) dict.erase(word);
            unordered_set<string> nextLevel;
            bool done = false; //in case of invalid further searching;
            for (auto &it: forward) //traverse each word in the forward -> the current level of the tree;
            {
                string word = it;
                for (auto &c: word) 
                {
                    char c0 = c; //store the original;
                    for (c = 'a'; c <= 'z'; ++c) //try each case;
                    {
                        if (c != c0) //avoid futile checking;
                        {
                            if (backward.count(word))  //using count is an accelerating method;
                            {
                                done = true;
                                !reversed ? tree[it].push_back(word) : tree[word].push_back(it); //keep the tree generation direction consistent;
                            }
                            else if (!done && dict.count(word))
                            {
                                nextLevel.insert(word);
                                !reversed ? tree[it].push_back(word) : tree[word].push_back(it);
                            }
                        }
                    }
                    c = c0; //restore the word;
                }
            }
            return done || buildTree(nextLevel, backward, dict, tree, reversed);
        }

        void getPath(string &beginWord, string &endWord, unordered_map<string, vector<string> > &tree, vector<string> &path, vector<vector<string> > &paths) //using reference can accelerate;
        {
            if (beginWord == endWord) paths.push_back(path); //till the end;
            else
            {
                for (auto &it: tree[beginWord]) 
                {
                    path.push_back(it);
                    getPath(it, endWord, tree, path, paths); //DFS retrieving the path;
                    path.pop_back();
                }
            }
        }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-25 16:18
Description : Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,
Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
Source      : https://leetcode.com/problems/word-ladder/
*******************************************/
#include <string>
#include <unordered_set.h>
using namespace std;
class Solution
{
    public:
        //AC - 59ms;
        int ladderLength(string bWord, string eWord, unordered_set<string>& wordList)
        {
            if(bWord == eWord) return 1;
            unordered_set<string> bList, eList;
            bList.insert(bWord);
            eList.insert(eWord);
            wordList.erase(bWord);
            wordList.erase(eWord);
            int len = 1;
            while(!bList.empty()&&!eList.empty())
            {
                if(bList.size() > eList.size()) bList.swap(eList);
                unordered_set<string> tmpList;
                for(auto cur: bList) //access by value, it will be copied;
                {
                    for(auto &c: cur) //access by reference, it will be directly accessed;
                    {
                        char c0 = c;
                        for(c = 'a'; c <= 'z'; c++)
                        {
                            if(c != c0) //avoid invalid further checking;
                            {
                                if(eList.count(cur)) return len+1;
                                if(wordList.count(cur)) //build up intermediate set and removing noise;
                                {
                                    tmpList.insert(cur);
                                    wordList.erase(cur);
                                }
                            }
                        }
                        c = c0;
                    }
                }
                bList.swap(tmpList); //update bList;
                len++;
            }
            return 0;
        }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 11:03
Description : 
Source      : https://leetcode.com/problems/longest-consecutive-sequence/
*******************************************/
#include <unordered_map.h>
void sort(int* nums, int begin, int end)
{
    int l=begin, r=end;
    int v = nums[l+(r-l)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            int t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            l++; r--;
        }
    }
    if(begin < r)
         sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

//AC - 4ms;
int longestConsecutive0(int* nums, int size)
{
    sort(nums, 0, size-1);
    int max = 1;
    int count = 1;
    for(int i = 1; i < size; i++)
    {
        if(nums[i] == nums[i-1]) continue; //just ignore the equivalent elements;
        if(nums[i] == nums[i-1]+1) count++;
        else  //there is a gap - nonconsecutive;
        {
            max = max > count? max : count;
            count = 1; //reset counter;
        }
    }
    max = max > count? max : count; //collect the last section;
    return max;
}

class Solution
{
    public:
        //AC - 28ms;
        int longestConsecutive0(vector<int>& nums)
        {
            unordered_map<int, int> map;
            int ret = 0;
            for(auto &i: nums)
            {
                if(map[i]) continue;
                if(!map.count(i-1) && !map.count(i+1))
                {
                    ret = max(ret, map[i]=1);
                    continue;
                }
                if(!map.count(i-1)) //only map[i+1];
                {
                    ret = max(ret, map[i]=map[i+map[i+1]]=map[i+1]+1); //set left and right boundary;
                    continue;
                }
                if(!map.count(i+1)) //only map[i-1];
                {
                    ret = max(ret, map[i]=map[i-map[i-1]]=map[i-1]+1);
                    continue;
                }
                ret = max(ret, map[i]=1, map[i-map[i-1]]=map[i+map[i+1]]=1+map[i-1]+map[i+1]);
            }
            return ret;
        }

        //AC - 24ms;
        int longestConsecutive1(vector<int>& nums)
        {
            int ret = 0;
            unordered_map<int, int> map;
            for(int &n: nums)
            {
                if(!map.count(n))
                {
                    int left = map.count(n-1)? map.at(n-1) : 0;
                    int right = map.count(n+1)? map.at(n+1) : 0;
                    int sum = left+right+1;
                    map[n] = sum;
                    if(sum > ret) ret = sum;
                    map[n-left] = map[n+right] = sum;
                }
            }
            return ret;
        }

        //AC - 20ms - quite different solution;
        int longestConsecutive(vector<int>& nums)
        {
            unordered_set<int> set(nums.begin(), nums.end());
            int ret = 1;
            for(auto &n: nums)
            {
                if(!set.count(n)) continue;
                set.erase(n);
                int pre=n-1, next=n+1;
                while(set.count(pre)) set.erase(pre--);
                while(set.count(next)) set.erase(next++);
                ret = max(ret, next-pre-1);
            }
            return ret;
        }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-17 16:49
Description : Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.
For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].
Source      : https://leetcode.com/problems/word-break-ii/
*******************************************/
#include <string.h>
#include <vector.h>
class Solution {
private: //DFS path build function
    void buildPath(bool isBreakable[], string &s, int startIndex, vector<string> &res, string sub, unordered_set<string>& wordDict, int minlen, int maxlen)
    {
        int i, len = s.size(); //i is the length of the substring;
        for(i =minlen; i<= min(maxlen, len - startIndex); ++i)
        {
            if(isBreakable[startIndex+i] && wordDict.count(s.substr(startIndex,i))) 
            {
                if(startIndex+i == len) res.push_back(sub + s.substr(startIndex,i));
                else buildPath(isBreakable, s, startIndex+i, res, sub + s.substr(startIndex,i) + " ", wordDict, minlen, maxlen);
            }
        }
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) 
    {
        int sSize = s.size(), len, i, minlen = INT_MAX, maxlen = INT_MIN;
        vector<string> res;
        bool isBreakable[sSize+1];
        fill_n(isBreakable, sSize+1, false);
        // find the minimum and maximum word length to accelerate the searching process;
        for (string word : wordDict) 
        { 
            minlen = min(minlen, (int)word.length());
            maxlen = max(maxlen, (int)word.length()); 
        }        
        //DP to build isBreakable
        for(i=sSize-minlen, isBreakable[sSize]= true; i>=0; --i)
        {
            for(len=minlen; len<=min(maxlen, sSize-i); ++len)
            {
                if(isBreakable[i+len] && wordDict.count(s.substr(i,len)) ) 
                {
                    isBreakable[i] = true; break;
                }
            }
        }
        //if breakable, do DFS path building
        if(isBreakable[0]) buildPath(isBreakable, s, 0, res, "", wordDict, minlen, maxlen);
        return res;
    }
};

/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 22:19
Description : Follow up for "Find Minimum in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
The array may contain duplicates.
Source      : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
*******************************************/
//AC - 4ms;
int findMin0(int* nums, int size) //linear solution;
{
    int c=0, n=0, nn=0;
    while(c < size)
    {
        n = c + 1;
        nn = n + 1;
        if(n<size && nums[n]<nums[c])
            return nums[n];
        if(nn<size && nums[nn]<nums[n])
            return nums[nn];
        c = nn;
    }
    return nums[0];
}

int findMin1(int* nums, int size)
{
    if(size == 1) return nums[0];
    int l=0, r=size-1, m=0;
    while(nums[l] >= nums[r]) //ensure the landscape to be reversed;
    {
        m = (l+r)>>1;
        if(r-l == 1) break;
        if(nums[m] > nums[l]) l = m;
        else if(nums[m] < nums[l]) r = m;
        else l++; //quite essential;
    }
    return nums[l]>nums[r]? nums[r]:nums[l];
}

int findMin(int* nums, int size)
{
    int l=0, r=size-1, m=0;
    while(l < r)
    {
        m = l+(r-l)/2;
        if(nums[m] > nums[r]) l = m+1;
        else if(nums[m] < nums[r]) r = m; //keep the middle element;
        else r--; 
    }
    return nums[l];
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-01 22:42
Description : 
Source      : https://leetcode.com/problems/fraction-to-recurring-decimal/
*******************************************/
#include <limits.h>
#define LEN 10000
struct MyListNode
{
    long long key;
    int val;
    struct MyListNode *next;
};

void push(struct MyListNode* head, long long key, int val)
{
    struct MyListNode *p = head;
    while(p->next)
        p = p->next;
    struct MyListNode *t = (struct MyListNode*)malloc(sizeof(struct MyListNode));
    t->key = key;
    t->val = val;
    p->next = t;
}

int pop(struct MyListNode* head, long long key)
{
    struct MyListNode *p = head->next;
    while(p)
    {
        if(p->key == key)
            return p->val;
        p = p->next;
    }
    return 0;
}

//AC - 4ms;
char* fractionToDecimal(int n, int d)
{
    if(n == 0) return "0";
    char *s = (char*)malloc(sizeof(char)*LEN);
    int index = 0;
    if((n<0 && d>0) || (n>0 && d<0)) s[index++] = '-'; //get the sign part;
    long long numerator = (n==INT_MIN)? -1*(long long)n : abs(n); //get the positive format of numerator;
    long long denominator = (d==INT_MIN)? -1*(long long)d : abs(d); //get the positive format of denominator;
    long long integer = numerator/denominator; //collecting the integer part;
    if(integer == 0)
        s[index++] = '0';
    else
    {
        char *t = (char*)malloc(sizeof(char)*LEN); //used to store the integer part in reverse order;
        int index0 = 0;
        while(integer)
        {
            t[index0++] = integer%10+'0';
            integer /= 10;
        }
        for(int i = index0-1; i > -1; i--) //reverse it again, then s will store the integer part in normal sequence;
            s[index++] = t[i];
    }
    long long remainder = numerator%denominator; //get the remainder by mod operator;
    if(remainder == 0)  //no remainder then just terminate the result and return;
    {
        s[index] = '\0';
        return s;
    }
    s[index++] = '.'; //there are remainder - decimals;
    struct MyListNode *head = (struct MyListNode*)malloc(sizeof(struct MyListNode)); //used to store the remainder digit index in string for recurring;
    while(remainder)
    {
        int pre = pop(head, remainder);
        if(pre) //check if this digit has already occurred, if so, add brackets;
        {
            for(int i = index; i > pre; i--)
                s[i] = s[i-1];
            index++;
            s[pre] = '(';
            s[index++] = ')';
            break;
        }
        push(head, remainder, index);
        remainder *= 10; //imitating division process here, retrieving the high decimal digit;
        s[index++] = remainder/denominator+'0';
        remainder %= denominator;
    }
    s[index] = '\0';
    return s;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-18 11:09
Description : 
Source      : https://leetcode.com/problems/shortest-palindrome/
*******************************************/
#include <stdlib.h>
//AC - 0ms - KMP;
//http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
char* shortestPalindrome(char* s) 
{
    if (!s || !*s) return strdup("");
    const int N = strlen(s);
    const int HN = (N >> 1);
    int next[HN], k, i, ch;

    //get the array of the longest length that the prefix matches the suffix;
    k = next[0] = 0;
    for (i = 1; i < HN; i++) 
    {
        ch = s[i]; //record the current character;
        while ((k > 0) && (ch != s[k])) k = next[k - 1]; //searching the longest suffix matching the prefix;
        if (ch == s[k]) k++;
        next[i] = k;
    }

    //using the array next to search reversely;
    for (i = N - 1, k = 0; i >= k; i--) 
    {
        ch = s[i];
        while ((k > 0) && (ch != s[k])) k = next[k - 1];
        if (ch == s[k]) k++; //the length that matches;
    }

    // Finally, only (N - i - k - 1) chars need to be added to make the shortest palindrome
    int len = N - (i + k);
    char* ret = (char*)malloc((len + N)* sizeof(char));
    if (ret != NULL) 
    {
        char* p = ret;
        for (i = N - 1; i > N - len; i--) *p++ = s[i];
        strcpy(p, s);
    }
    return ret;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-04-20 15:48
Description : Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".
Source      : https://leetcode.com/problems/shortest-palindrome/
Reference   : http://articles.leetcode.com/longest-palindromic-substring-part-ii
*******************************************/
#include <vector.h>
#include <string.h>
class Solution 
{
public:
    //AC - 16ms;
    string shortestPalindromeUsingManacher(string s) 
    {
        string T = "^";
        for(int i = 0; i < s.size(); i++)
            T += "#" + s.substr(i,1);
        T += "#@";
        int n = T.size();
        vector<int> P(n, 0);
        int R = 0, C = 0;
        for(int i = 1; i < n - 1; i++)
        {
            int i_mirr = 2 * C - i;
            P[i] = i < R ? min(P[i_mirr], R - i) : 0;
            while(T[i + P[i] + 1] == T[i - P[i] - 1])
            {
                P[i]++;
                if(i + P[i] > R)
                {
                    C = i;
                    R = i + P[i];
                }
            }
        }
        int maxLen = 0;
        for(int i = 1; i < n - 1; i++)
            if(i - P[i] == 1) maxLen = max(maxLen, P[i]); // only consider palindrome starting from beginning position
        string append = s.substr(maxLen, s.size() - maxLen);
        reverse(append.begin(), append.end());
        return append + s;
    }
    //AC - 8ms;
    string shortestPalindromeUsingKMP(string s) 
    {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s;
        vector<int> p(l.size(), 0);
        for (int i = 1; i < l.size(); i++) 
        {
            int j = p[i - 1];
            while (j > 0 && l[i] != l[j]) j = p[j - 1];
            if(l[i] == l[j]) j++;
            p[i] = j;
        }
        return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
    }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-12 15:49
Description : A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

 Buildings  Skyline Contour
 The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

 For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8]  ] .

 The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ...  ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

 For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0]  ].

Notes:

The number of buildings in any input list is guaranteed to be in the range [0, 10000].
The input list is already sorted in ascending order by the left x position Li.
The output list must be sorted by the x position.
There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
Source      : https://leetcode.com/problems/the-skyline-problem/
*******************************************/
#include <vector.h>
class Solution
{
public:
    //AC - 806ms;
    //https://leetcode.com/discuss/37630/my-c-code-using-one-priority-queue-812-ms
    vector<pair<int, int>> getSkyline(vector<vector<int>> buildings)
    {
        vector<pair<int, int>> res;
        int cur=0, curX, curH, len=buildings.size();
        priority_queue<pair<int, int>> liveBlg;
        while(cur<len || !liveBlg.empty())
        {
            if(liveBlg.empty() || (cur<len && buildings[cur][0]<=liveBlg.top().second))
            {
                curX = buildings[cur][0];
                while(cur<len && buildings[cur][0]==curX)
                {
                    liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
                    cur++;
                }
            }
            else
            {
                curX = liveBlg.top().second;
                while(liveBlg.size() && liveBlg.top().second<=curX) liveBlg.pop();
            }
            curH = liveBlg.empty()? 0:liveBlg.top().first;
            if(res.empty() || res.back().second!=curH)
                res.push_back(make_pair(curX, curH));
        }
        return res;
    }

    //AC - 836ms;
    //https://leetcode.com/discuss/67091/once-for-all-explanation-with-clean-java-code-nlog-time-space
    vector<pair<int, int>> getSkyline1(vector<vector<int>> buildings)
    {
        vector<pair<int, int>> coordinates, res;
        int pre=0, cur=0;
        for(int i = 0; i < buildings.size(); i++)
        {
            vector<int> v = buildings[i];
            coordinates.push_back(make_pair(v[0], -v[2]));
            coordinates.push_back(make_pair(v[1], v[2]));
        }
        sort(coordinates.begin(), coordinates.end());
        multiset<int> heap;
        heap.insert(0);
        for(int i = 0; i < coordinates.size(); i++)
        {
            pair<int, int> t = coordinates[i];
            if(t.second < 0) heap.insert(-t.second);
            else heap.erase(heap.find(t.second));
            cur = *(heap.rbegin());
            if(cur != pre)
            {
                res.push_back(make_pair(t.first, cur));
                pre = cur;
            }
        }
        return res;
    }
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-29 14:41
Description : 
Source      : https://leetcode.com/problems/basic-calculator/
*******************************************/
#include <bool.h>
//AC - 4ms;
int calculate(char* s)
{
    int* signs = (int*)malloc(sizeof(int)); //used to store the signs before opening bracket;
    int top = -1;
    signs[++top] = 1;
    int sign = 1;
    int num = 0;
    int ret = 0; //used to store the result;
    while(*s)
    {
        if(*s>='0' && *s<='9')  //collect the number between non-digits;
        {
            num = 10*num + *s - '0';
        }
        else if(*s=='+' || *s=='-') //add the previous number and reset sign;
        {
            ret += signs[top]*sign*num;
            num = 0;
            sign = (*s=='+'? 1 : -1);
        }
        else if(*s == '(') //store the sign before opening bracket;
        {
            signs = (int*)realloc(signs, sizeof(int)*(top+2));
            signs[top+1] = sign*signs[top]; //to avoid evaluation sequence problem, moving top++ to another statement;
            top++;
            sign = 1;
        }
        else if(*s == ')') //add the previous number and delete a sign for this pair of brackets;
        {
            ret += signs[top--]*sign*num;
            num = 0;
        }
        s++;
    }
    if(num) //if there is still number left;
        ret += signs[top]*sign*num;
    return ret;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-15 15:46
Description : Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
Source      : https://leetcode.com/problems/majority-element-ii/
*******************************************/
//AC - 8ms;
//Boyer-Moor Majority Vote Algorithm;
int* majorityElement0(int* nums, int size, int *returnSize)
{
    int count1 = 0, count2 = 0;
    int a, b;
    for(int i = 0; i < size; i++)
    {
        if(count1 == 0 || nums[i] == a)
            count1++, a = nums[i];
        else if(count2 == 0 || nums[i] == b)
            count2++, b = nums[i];
        else
            count1--, count2--;
    }
    count1 = count2 = 0;
    for(int i = 0; i < size; i++)
        if(nums[i] == a) 
            count1++;
        else if(nums[i] == b)
            count2++;
    int* res = (int*)malloc(sizeof(int)*2);
    int index = 0;
    if(count1 > size/3) 
        res[index++] = a;
    if(count2 > size/3)
        res[index++] = b;
    *returnSize = index;
    return res; 
}

//AC - 8ms;
int* majorityElement1(int* nums, int size, int *returnSize)
{
    int count1 = 0, count2 = 0;
    int a, b;
    for(int i = 0; i < size; i++)
    {
        if(nums[i] == a)
            count1++;
        else if(nums[i] == b)
            count2++;
        else 
        {
            if(count1 == 0)
                a = nums[i], count1 = 1;
            else if(count2 == 0)
                b = nums[i], count2 = 1;
            else
                count1--, count2--;
        }
    }
    count1 = count2 = 0;
    for(int i = 0; i < size; i++)
        if(nums[i] == a) 
            count1++;
        else if(nums[i] == b)
            count2++;
    int* res = (int*)malloc(sizeof(int)*2);
    int index = 0;
    if(count1 > size/3) 
        res[index++] = a;
    if(count2 > size/3)
        res[index++] = b;
    *returnSize = index;
    return res; 
}


//Generalized Boyer Moor Algorithm for 1/k;
int* majorityElement2(int* nums, int size, int* returnSize)
{
    int splitter = 2;//more than 1/3 so at most there will be 2 elements; as for 1/4 there will be at most 3 accordingly;
    int *elements = (int*)malloc(sizeof(int)*splitter);
    int *counts = (int*)malloc(sizeof(int)*splitter);
    int *res = (int*)malloc(sizeof(int)*splitter);
    for(int i = 0; i < size; i++)
    {
        int j = 0;
        for(; j < splitter; j++)
            if(elements[j] == nums[i])
            {
                counts[j]++;
                break;
            }
        if(j != splitter)
            continue;
        for(j = 0; j < splitter; j++)
            if(counts[j] == 0)
            {
                elements[j] = nums[i];
                counts[j] = 1;
                break;
            }
        if(j != splitter)
            continue;
        for(j = 0; j < splitter; j++)
            counts[j]--;
    }
    int index = 0;
    for(int i = 0; i < splitter; i++)
    {
        if(counts[i] == 0)
            continue;
        counts[i] = 0;
        for(int j = 0; j < size; j++)
            if(elements[i] == nums[j])
                counts[i]++;
        if(counts[i] > size/(splitter+1))
            res[index++] = elements[i];
    }
    *returnSize = index;
    return res;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 10:44
Description : You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
Source      : https://leetcode.com/problems/substring-with-concatenation-of-all-words/
*******************************************/
#include <vector.h>
class Solution {
    public:
        vector<int> findSubstring(string s, vector<string>& words) 
        {
            unordered_map<string, int> counts;
            for (string word : words) counts[word]++;
            int n = s.length(), num = words.size(), len = words[0].length();
            vector<int> indexes;
            for (int i = 0; i < n - num * len + 1; i++) 
            {
                unordered_map<string, int> seen;
                int j = 0;
                for (; j < num; j++) 
                {
                    string word = s.substr(i + j * len, len);
                    if (counts.find(word) != counts.end()) 
                    {
                        if (seen[word]++ >= counts[word]) break;
                    }
                    else break;
                }
                if (j == num) indexes.push_back(i);
            }
            return indexes;
        }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-09 16:38
Description : Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
Source      : https://leetcode.com/problems/range-sum-query-mutable/
Reference   : http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
Reference   : http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
*******************************************/
struct NumArray
{
    int *nums, *sums;
    int size;
};

//partial sums are stored in numArray->sums;
//index of sums are 1 more than that in nums;
void updateElement(struct NumArray* numArray, int i, int val)
{
    i++;
    while(i <= numArray->size)
    {
        numArray->sums[i] += val;
        i += (i & -i); //move to its parent i UpdateView;
    }
}

struct NumArray* NumArrayCreate(int *nums, int size)
{
    struct NumArray *t = (struct NumArray*)malloc(sizeof(struct NumArray));
    t->nums = (int*)malloc(sizeof(int)*size);
    memcpy(t->nums, nums, sizeof(int)*size);
    t->size = size;
    t->sums = (int*)malloc(sizeof(int)*(size+1));
    memset(t->sums, 0, sizeof(int)*(size+1));
    for(int i = 0; i <= size; i++)
        updateElement(t, i, nums[i]);
    return t;
}

void update(struct NumArray* numArray, int i, int val)
{
    int d = val-numArray->nums[i];
    numArray->nums[i] = val;
    updateElement(numArray, i, d);
}

//partial sums are stored in numArray->sums;
//index of sums are 1 more than that in nums;
int getSum(struct NumArray* numArray, int i)
{
    int sum = 0;
    i++;
    while(i > 0)
    {
        sum += numArray->sums[i];
        i -= (i & -i); //move to its parent in getSumView;
    }
    return sum;
}
int sumRange(struct NumArray* numArray, int i, int j)
{
    return getSum(numArray, j)-getSum(numArray, i-1);
}

void NumArrayFree(struct NumArray* numArray)
{
    free(numArray->nums);
    free(numArray->sums);
    free(numArray);
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 20:42
Description : Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.
Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.
Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.
Source      : https://leetcode.com/problems/count-of-range-sum/
*******************************************/
#include <limits.h>
#include <stdlib.h>
void swap(long*p, long*q)
{
    long t = *p;
    *p = *q;
    *q = t;
}

void swiftSort(long* arr, int low, int high)
{
    int l = low, r = high;
    long v = arr[l+(r-l)/2];
    while(l <= r)
    {
        while(arr[l] < v) l++;
        while(arr[r] > v) r--;
        if(l <= r)
        {
            swap(arr+l, arr+r);
            l++, r--;
        }
    }
    if(r > low)
        swiftSort(arr, low, r);
    if(l < high)
        swiftSort(arr, l, high);
}

int indexOf(long* arr, int size, double a)
{
    int l = 0, r = size-1, m;
    while(l <= r)
    {
        m = l + (r-l)/2;
        arr[m] <= a? (l=m+1) : (r=m-1);
    }
    return l;
}

int counter(long* nums, int l, int h, int low, int high)
{
    if(h == l)
        return (nums[l] >= low && nums[l] <= high)? 1:0;
    int m = l + (h-l)/2;
    int count = 0;
    int tmpSize = h-m;
    long *arr = (long*)malloc(sizeof(long)*tmpSize);
    long sum = 0;
    for(int i = m+1; i <= h; i++)
    {
        sum += nums[i];
        arr[i-m-1] = sum;
    }
    swiftSort(arr, 0, tmpSize-1);
    sum = 0;
    for(int i = m; i >= l; i--)
    {
        sum += nums[i];
        count += indexOf(arr, tmpSize, high-sum+0.5) - indexOf(arr, tmpSize, low-sum-0.5);
    }
    return counter(nums, l, m, low, high) + counter(nums, m+1, h, low, high) + count;
}

//AC - 72ms - Divide and Conquer;
int countRangeSum(int* nums, int size, int low, int high)
{
    if(size == 0)
        return 0;
    long *a = (long*)malloc(sizeof(long)*size);
    for(int i = 0; i < size; i++)
        nums[i] == INT_MIN? (a[i] = -1*INT_MIN) : (a[i] = nums[i]);
    return counter(a, 0, size-1, low, high);
}

#include <vector.h>

class Solution 
{  
public:
    // return last index <= hint.
    int BinarySearch(const vector<long long> &ranges, const long long hint) 
    {
        int begin = 0;
        int end = ranges.size();
        while (begin < end) 
        {
            int mid = begin + (end - begin) / 2;
            if (hint < ranges[mid]) end = mid;
            else begin = mid + 1;
        }
        return end - 1;
    }

    long long SumBIT(const vector<long long> &bit, int idx) 
    {
        long long sum = 0;
        while (idx > 0) 
        {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    //updating process;
    void AddBIT(vector<long long> &bit, int idx, int value) 
    {
        const int n = bit.size();
        while (idx < n) 
        {
            bit[idx] += value;
            idx += (idx & -idx);
        }
    }

    vector<long long> BuildPrefixSum(const vector<int> &nums) 
    {
        vector<long long> prefix_sums(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); ++i) prefix_sums[i] = prefix_sums[i - 1] + nums[i - 1];
        return prefix_sums;
    }

    vector<long long> BuildSortedRanges(const vector<long long> &prefix_sums) 
    {
        // remove duplicates.
        set<long long> help(prefix_sums.cbegin(), prefix_sums.cend());
        // make sure BinarySearch not return zero. This is *important*!
        help.insert(LLONG_MIN);
        // return sorted array.
        return vector<long long>(help.begin(), help.end());
    }

    //AC - using Fenwick Tree (Binary Indexed Tree);
    //reference: http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.empty()) return 0;
        const int n = nums.size();
        auto prefix_sums = BuildPrefixSum(nums);
        auto ranges = BuildSortedRanges(prefix_sums);
        vector<long long> bit(ranges.size(), 0);
        for (int i = 0; i <= n; ++i) // mark prefix sums.
            AddBIT(bit, BinarySearch(ranges, prefix_sums[i]), 1);
        int count = 0;
        for (int i = 0; i < n; ++i) 
        {
            // make prefix_sums[i] invisible.
            AddBIT(bit, BinarySearch(ranges, prefix_sums[i]), -1);
            // count the number of valid ranges.
            count += SumBIT(bit, BinarySearch(ranges, upper + prefix_sums[i]));
            count -= SumBIT(bit, BinarySearch(ranges, lower + prefix_sums[i] - 1));
        }
        return count;
    }

    //AC - 100ms - using multiset sorting feature;
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.empty()) return 0;
        const int n = nums.size();
        auto prefix_sums = BuildPrefixSum(nums);
        int count = 0;
        multiset<long long> ordered_sums;
        for (int i = n; i >= 1; --i) 
        {
            ordered_sums.insert(prefix_sums[i]);
            auto lb_iter = ordered_sums.lower_bound(lower + prefix_sums[i - 1]);
            auto ub_iter = ordered_sums.upper_bound(upper + prefix_sums[i - 1]);
            count += distance(lb_iter, ub_iter);
        }
        return count;
    }
};


class Solution {
    struct SegmentTree 
    {
        SegmentTree* left;
        SegmentTree* right;
        int count;
        long min;
        long max;
        // constructing the SegmentTree - nums have been sorted
        SegmentTree(vector<long>& nums, int l, int r):left(NULL),right(NULL) 
        {
            if (l>r) return;
            min = nums[l];
            max = nums[r];
            count=0;
            if (l==r) return;
            int m = (l+r)/2;
            if (l<=m) left = new SegmentTree(nums, l,m);
            else left=NULL;
            if (m+1<=r) right = new SegmentTree(nums, m+1, r);
            else right = NULL;
        }

        //update process;
        void add(long value) 
        {
            if (value<min || value>max) return;
            count++;
            if (left && value<=left->max) left->add(value);
            else if (right && value>=right->min) right->add(value);
        }

        //getSum process;
        int getCount(long minValue, long maxValue) 
        {
            if (minValue<=min && max<=maxValue) return count;
            if (maxValue<min || minValue>max) return 0;
            int leftCount = left ? left->getCount(minValue, maxValue) : 0;
            int rightCount = right ? right->getCount(minValue, maxValue) : 0;
            return leftCount+rightCount;
        }
    };


public:
    //AC - 48ms - SegmentTree using the prefixSum to indicate the range of the node and 
    //an extra variable count to record the count of the prefixSum that is within the range;
    //reference: https://codelucid.wordpress.com/2015/05/27/segment-trees/
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.size()==0) return 0;
        unordered_set<long> values;
        long sum = 0;
        for(int i=0;i<nums.size();++i) 
        {
            sum+=nums[i];
            values.insert(sum);
        }
        vector<long> sums;
        for(auto& v : values) sums.push_back(v);
        sort(sums.begin(), sums.end());
        SegmentTree* tree = new SegmentTree(sums, 0, sums.size()-1);
        int count = 0;
        for(int i=nums.size()-1;i>=0;i--) 
        {
            tree->add(sum);
            sum-=nums[i];
            count += tree->getCount(lower+sum, upper+sum);
        }
        return count;
    }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 16:46
Description : Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Source      : https://leetcode.com/problems/search-in-rotated-sorted-array/
*******************************************/
int searchIndex0(int* nums, int begin, int end, int target)
{
    if(end < begin) return -1;
    int m = (begin+end)/2;
    int mid = nums[m];
    if(nums[m] == target) return m;
    else
    {
        int right = searchIndex(nums, m+1, end, target);
        return right==-1? searchIndex(nums, begin, m-1, target) : right;
    }
}

//AC - 0ms;
int search0(int* nums, int size, int target)
{
    return searchIndex(nums, 0, size-1, target);
}

int search1(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m = (l+r)/2;
        if(nums[m] == target) return m;
        if(nums[l] <= nums[m])
        {
            if(nums[l]<=target && target<nums[m]) r = m-1;
            else l = m+1;
        }
        else
        {
            if(nums[m]<target && target<=nums[r]) l = m+1;
            else r = m-1;
        }
    }
    return nums[l]==target? l : -1;
}

//AC - 0ms;
//actually the rotating process is a right-moving process;
int search(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r) //searching for the rotating position;
    {
        int m=(l+r)/2;
        if(nums[m]>nums[r]) l=m+1;
        else r=m;
    }
    int s = l;
    l=0, r=size-1;
    while(l <= r)
    {
        int m = (l+r)/2;
        int real = (m+s)%size;
        if(nums[real] == target) return real;
        if(nums[real] < target) l=m+1;
        else r=m-1;
    }
    return -1;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-28 15:51
Description : You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise.
Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.
Example 1:
Given x = [2, 1, 1, 2],
┌───┐
│   │
└───┼──>
    │
Return true (self crossing)
Example 2:
Given x = [1, 2, 3, 4],
┌──────┐
│      │
│
│
└────────────>
Return false (not self crossing)
Example 3:
Given x = [1, 1, 1, 1],
┌───┐
│   │
└───┼>
Return true (self crossing)
Source      : https://leetcode.com/problems/self-crossing/
*******************************************/
#include <bool.h>
//AC - 0ms;
//https://leetcode.com/discuss/89336/the-best-submission-searching-for-crossing-pattern-the-key
bool isSelfCrossing(int* x, int size)
{
    for(int i = 3; i < size; i++)
    {
        if(x[i]>=x[i-2] && x[i-1]<=x[i-3]) return true;
        if(i>=4 && x[i-1]==x[i-3] && x[i]+x[i-4]>=x[i-2]) return true;
        if(i>=5 && x[i-2]-x[i-4]>=0 && x[i]>=x[i-2]-x[i-4] && x[i-1]>=x[i-3]-x[i-5] && x[i-1]<=x[i-3]) return true;
    }
    return false;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-10 08:02
Description : Given a list of unique words. Find all pairs of indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
Source      : https://leetcode.com/problems/palindrome-pairs/
*******************************************/
#include <string.h>
#include <vector.h>
class Solution 
{
private:
    bool isPal(string& s, int start, int end)  //start and end refer to index;
    {
        while(s[start] == s[end]) start++, end--;
        return start >= end;
    }

public:
    //AC - 256ms;
    vector<vector<int>> palindromePairs(vector<string>& words) 
    {
        vector<vector<int>> result;
        if(words.empty()) return result;
        unordered_map<string, int> table; //words and its corresponding index;
        for(int i = 0; i < words.size(); i++) table[words[i]]=i;
        for(int i = 0; i < words.size(); i++) 
        {
            string cur = words[i];
            reverse(cur.begin(), cur.end());
            int t=0, len=cur.size();
            for(int l = 0; l <= len; l++) //l is the length of the sub-string;
            {
                if(isPal(cur,0, l-1))  //the current word will work as prefix;
                {
                    string tmp = cur.substr(l);
                    if(table.count(tmp))  //accelerate the checking process;
                    {
                        t = table[tmp];
                        if((t!=i) && (len>=words[t].size())) //avoid duplicates;
                        result.push_back(vector<int>{i, t}); //the matched word will be the suffix;
                    }
                }
                if(isPal(cur, l, len-1)) //the current word will work as suffix;
                {
                    string tmp = cur.substr(0,l); 
                    if(table.count(tmp)) 
                    {
                        t = table[tmp];
                        if((t!=i) && (len>words[t].size())) //avoid duplicates;
                        result.push_back(vector<int>{t, i}); //the matched word the prefix;
                    }
                }
            }
        }
        return result;
    }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-24 16:04
Description : Given an array of strings, group anagrams together.
For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
["ate", "eat","tea"],
["nat","tan"],
["bat"]
]
Note:
For the return value, each inner list's elements must follow the lexicographic order.
All inputs will be in lower-case.
Source      : https://leetcode.com/problems/anagrams/
*******************************************/
#include <vector.h>
//using multiset<string> to auto-sort strings inserted;
//using count sort instead of built-in sort to accelerate;
class Solution {
    public:
        //AC - 60ms;
        vector<vector<string>> groupAnagrams0(vector<string>& strs) 
        {
            unordered_map<string, vector<string>> map;
            for(auto &v: strs)
            {
                string t(v);
                sort(t.begin(), t.end());
                map[t].push_back(v);
            }
            vector<vector<string>> result(map.size());
            int k = 0;
            for(auto iter = map.begin(); iter != map.end(); ++iter, ++k)
            {
                result[k].swap(iter->second);
                sort(result[k].begin(), result[k].end());
            }
            return result;
        }
        
        //AC - 76ms;
        vector<vector<string>> groupAnagrams(vector<string>& strs) 
        {
            vector<vector<string>> result;
            unordered_map<string, multiset<string>> dict;
            for(auto str : strs)
            {
                string t = str;
                //sort(t.begin(), t.end());
                t = countSort(t);
                dict[t].insert(str);
            }
            for(auto a : dict)
            {
                vector<string> temp(a.second.begin(), a.second.end());
                result.push_back(temp);
            }
            return result;
        }

        /** use the count sort to accelerate the sorting process **/
        string countSort(string &s)
        {
            vector<int> c(26, 0);
            int n=s.size();
            for(int i=0; i<n; i++)  c[s[i]-'a']++;
            int p=0;
            string t(n, 'a');
            for(int j=0; j<26; j++)
            {
                for(int i=0; i<c[j]; i++)
                    t[p++]+=j;
            }
            return t;
        }
};
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-28 22:20
Description : The set [1,2,3,…,n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
Note: Given n will be between 1 and 9 inclusive.
Source      : https://leetcode.com/problems/permutation-sequence/
*******************************************/
void swap(int* p, int* q)
{
    int t = *p; *p = *q; *q = t;
}
void reverse(int* nums, int begin, int end)
{
    for(int i = begin; i < (begin+end+1)/2; i++)
        swap(nums+i, nums+end+begin-i);
}

//AC - 0ms;
char* getPermutation0(int n, int k)
{
    int *nums = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        nums[i] = i+1;
    k--;
    while(k)
    {
        int i=n-1, j=n-1;
        while(i>0 && nums[i]<=nums[i-1]) i--; //make sure the [i..n-1] is in descending order;
        while(nums[j] <= nums[i-1]) j--; //find the first bigger one backwards;
        swap(nums+j, nums+i-1); //ensure the next is bigger;
        reverse(nums, i, n-1); //since [i..n-1] is descending, after reverse it will be ascending and as a result - [i..n-1] will be the smallest - the smallest in the bigger results - the next permutation;
    }
    char *s = (char*)malloc(sizeof(char)*(n+1));
    for(int i = 0; i < n; i++)
        s[i] = nums[i]+'0';
    s[n] = '\0';
    return s;
}

//AC - 0ms;
//using permutation and combination basics;
char* getPermutation(int n, int k)
{
    char* arr = (char*)malloc(sizeof(char)*(n+1));
    int j, f=1;
    for(int i = 1; i <= n; i++)
    {
        f *= i; //n!;
        arr[i-1] = i+'0'; //containing the smallest;
    }
    k--;
    for(int i=0; i < n; i++)
    {
        f /= n-i; //the unit of the current position;
        j = i+k/f; //the number should be placed in the current position;
        char c = arr[j];
        for(; j > i; j--)
            arr[j] = arr[j-1];
        k %= f;
        arr[i] = c;
    }
    arr[n] = '\0'; //terminate the string;
    return arr;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-15 16:30
Description : Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
Source      : https://leetcode.com/problems/simplify-path/
*******************************************/

char* simplifyPath(char* path)
{
    int pre = 0, cur = 0;
    int index = 0;
    int size = strlen(path);
    if(size == 0)
        return "";
    //make sure the last character is a forward slash;
    if(*(path+size-1) != '/')
    {
        /*strcat(path, "/");//the space spared for path should be enough for another character - but in this case, it's not reliable;*/
        char* tmp = (char*)malloc(sizeof(char)*(size+2));
        strcpy(tmp, path);
        strcat(tmp, "/");
        path = tmp;
        size++;
    }
    //make sure the pre and cur point to the first forward slash;
    while(*(path+cur) != '/')
    {
        pre++;
        cur++;
    }
    int unitSize = 0;
    char* unit = (char*)malloc(sizeof(char)*(size+1));
    char** sArray = (char**)malloc(sizeof(char*) * size);
    for(; *(path+cur) != '\0'; cur++)
    {
        if(*(path+cur) == '/')
        {
            unitSize = cur - pre - 1;
            if(unitSize < 0)//pre and cur point to the same position;
                continue;
            strncpy(unit, path+pre+1, unitSize);//cur - pre > 0 is ensured;
            unit[unitSize] = '\0';
            pre = cur;
            if(strcmp(unit, ".") == 0 || strcmp(unit, "") == 0) //stay the same;
                continue;
            if(strcmp(unit, "..") == 0) //pop out;
            {
                //replacing this part with index > 0 ? index-- : index; will reduce the time from 8ms to 4ms;
                if(index > 0)
                    index--;
            }
            else
            {
                sArray[index] = (char*)malloc(sizeof(char) * (unitSize+1));
                strcpy(sArray[index++], unit);
            }
        }
    }
    //collecting the directories;
    if(index == 0)
        return "/";
    unit[0] = '/';
    unit[1] = '\0';
    unitSize = 0;
    for(int i = 0; i < index; i++)
    {
        unitSize += strlen(sArray[i]) + 1;
        strcat(unit, sArray[i]);
        strcat(unit, "/");
    }
    //overwriting the last forward slash if it's not root;
    unit[unitSize] = '\0';
    return unit;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-04 08:01
Description : Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.
Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
Source      : https://leetcode.com/problems/sort-colors/
*******************************************/
void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}

//AC - 0ms - one pass;
void sortColors0(int* nums, int size)
{
    if(size < 2) return;
    int index0=0, index2=size-1;
    int i = 0;
    while(i <= index2)
    {
        if(nums[i] == 0)
            swap(nums+index0++, nums+i++);
        else if(nums[i] == 2)
            swap(nums+index2--, nums+i);
        else i++;
    }
}

//AC - 0ms - two passes;
void sortColors1(int* nums, int size)
{
    if(size < 2) return ;
    int index0=0, index1=size-1;
    while(index0 != index1) //sort color ZERO;
    {
        while(nums[index0]==0 && index0<index1) index0++;
        while(nums[index1]!=0 && index0<index1) index1--;
        if(index0 != index1) swap(nums+index0, nums+index1);
    }
    index1 = size-1;
    while(index0 != index1) //sort color ONE;
    {
        while(nums[index0]==1 && index0<index1) index0++;
        while(nums[index1]!=1 && index0<index1) index1--;
        if(index0 != index1) swap(nums+index0, nums+index1);
    }
}

//AC - 0ms - one pass;
void sortColors2(int* nums, int size)
{
    int index0=0, index1=0, index2=0;
    for(int i = 0; i < size; i++)
        switch(nums[i])
        {
            case 0: nums[index2++]=2; nums[index1++]=1; nums[index0++]=0; break;
            case 1: nums[index2++]=2; nums[index1++]=1;  break;
            case 2: nums[index2++] = 2; break;
            default: break;
        }
}

void sortColors(int* nums, int size)
{
    int index0=0, index1=size-1;
    for(int i = 0; i < index1; i++)
    {
        if(nums[i] == 0) swap(nums+i, nums+index0++);
        if(nums[i] == 2) swap(nums+i--, nums+index1--);
    }
}

void sortKColors(int* nums, int size, int k)
{
    if(size < 2) return ;
    int color0=1, color1=k;
    int index0=0, index1=size-1;
    while(color0 < color1)
    {
        int i = index0;
        while(i <= index1)
        {
            if(nums[i] == color0)
                swap(nums+index0++, nums+i++);
            else if(nums[i] == color1)
                swap(nums+index1--, nums+i);
            else i++;
        }
        color0++, color1--;
    }
}
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
#include <limits.h>
//AC - 4ms;
#define LEN  128
char* minWindow(char* s, char* t)
{
    int counter[LEN] = {0};
    int start=0, end=0, tLen=strlen(t), sLen=strlen(s);
    int minStart=0, minLen=INT_MAX;
    for(int i = 0; i < LEN; i++) counter[i] = -sLen; //distinguish the letter in and not in t;
    for(int i = 0; t[i]; i++) counter[t[i]] = 0;
    for(int i = 0; t[i]; i++) counter[t[i]]++;
    while(end < sLen)
    {
        if(counter[s[end]]-- > 0) tLen--;
        end++; //move to the next character;
        while(tLen == 0) //a valid substring;
        {
            if(end-start < minLen) //collect the minimal only;
                minStart=start, minLen=end-start;
            counter[s[start]]++;
            if(counter[s[start]] > 0) tLen++; //if s[start] is in t;
            start++; //move forward by ignoring s[start];
        }
    }
    if(minLen != INT_MAX)
    {
        char* t = (char*)malloc(sizeof(char)*(minLen+1));
        *t = '\0';
        strncat(t, s+minStart, minLen);
        return t;
    }
    return "";
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-02 21:28
Description : Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
Source      : https://leetcode.com/problems/word-search/
*******************************************/
#include"utils.h"
//using recursive function to achieve backtracking;
//the termination conditions should be carefully handled;
bool isFound(char** board, int row, int col, char*word, int rIndex, int cIndex)
{
    if(*word == '\0') return true; //reach it end;
    if(rIndex>=row || cIndex>=col || rIndex<0 || cIndex<0 || *word!=board[rIndex][cIndex]) return false;
    char t = board[rIndex][cIndex];
    board[rIndex][cIndex] = '\0'; //avoid re-visiting;
    if(isFound(board, row, col, word+1, rIndex+1, cIndex) || isFound(board, row, col, word+1, rIndex-1, cIndex) || isFound(board, row, col, word+1, rIndex, cIndex+1) || isFound(board, row, col, word+1, rIndex, cIndex-1)) return true;
    board[rIndex][cIndex] = t; //restore to the original;
    return false; //if all failed, return false;
}

bool exist(char** board, int row, int col, char* word) 
{
    //Start from each position;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(isFound(board, row, col, word, i, j))
                return true;
    return false;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-23 21:07
Description : Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
Source      : https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
*******************************************/
#include <cstdbool.h>
bool search0(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m = (l+r)/2;
        if(nums[m] == target) return true;
        while(nums[l]==nums[m] && l!=m) l++;
        while(nums[r]==nums[m] && r!=m) r--;
        if(nums[l] <= nums[m])
        {
            if(nums[l]<=target && target<nums[m]) r = m-1;
            else l = m+1;
        }
        else
        {
            if(nums[m]<target && target<=nums[r]) l = m+1;
            else r = m-1;
        }
    }
    return nums[l]==target;
}

bool search(int* nums, int size, int target)
{
    int l=0, r=size-1;
    int m = 0;
    while(l < r)
    {
        m = (l+r)/2;
        if(nums[m] == target) return true;
        if(nums[m] > nums[r])
        {
            if(nums[m]>target && nums[l]<=target) r = m;
            else l = m+1;
        }
        else if(nums[m] < nums[r])
        {
            if(nums[m]<target && nums[r]>=target) l = m+1;
            else r = m;
        }
        else r--;
    }
    return nums[l]==target;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-20 21:15
Description : Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.
Source      : https://leetcode.com/problems/largest-rectangle-in-histogram/
*******************************************/
//AC - 8ms
//only calculate the stack - ascending order
//the width will be calculated by the stored indexes;
int largestRectangleArea(int* heights, int heightSize)
{
    heightSize++;
    int* tmp = (int*)malloc(sizeof(int) * heightSize);
    int i = 0;
    for(; i < heightSize - 1; i++)
        tmp[i] = heights[i];
    tmp[heightSize-1] = 0;
    heights = tmp;
    int current = 0, max = 0;
    int* stack = (int)malloc(sizeof(int) * heightSize);
    int top = 0;
    stack[top] = -1;
    for(i = 0; i < heightSize; i++)
    {
        while(top > 0 && heights[stack[top]] > heights[i])
        {
            current = (i - stack[top - 1] - 1) * heights[stack[top]];
            top--;
            if(current > max)
                max = current;
        }
        stack[++top] = i;
    }
    return max;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-19 11:19
Description : Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
Source      : https://leetcode.com/problems/maximal-rectangle/
*******************************************/
//AC - 4ms
int fixedMaximalRectangle(int* heights, int* stack, int size)
{
    int current = 0, max = 0; 
    int i = 0, j = 0;
    int top = 0;
    stack[top] = -1;
    for(; i < size; i++)
    {
        while(top > 0 && heights[stack[top]] > heights[i])
        {
            current = (i - stack[top - 1] - 1) * heights[stack[top]];
            top--;
            if(current > max)
                max = current;
        }
        stack[++top] = i;
    }
    return current > max? current : max;
}
int maximalRectangle(char** matrix, int rowSize, int colSize)
{
    colSize++;
    int* heights = (int*)malloc(sizeof(int) * colSize);
    int* stack = (int*)malloc(sizeof(int) * colSize);
    int i = 0, j = 0;
    int max = 0, current = 0; 
    for(j = 0; j < colSize; j++) 
    {
        heights[j] = 0;
        stack[j] = 0;
    }
    for(i = 0; i < rowSize; i++)
    {
        for(j = 0; j < colSize - 1; j++)
        {
            matrix[i][j] == '0' ? heights[j] = 0 : heights[j]++;
        }
        current = fixedMaximalRectangle(heights, stack, colSize);
        if(current > max)
           max = current; 
    }
    return max;
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-15 21:26
Description : Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

great
/    \
gr    eat
/ \    /  \
g   r  e   at
            / \
            a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

rgeat
/    \
rg    eat
/ \    /  \
r   g  e   at
            / \
            a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

rgtae
/    \
rg    tae
/ \    /  \
r   g  ta  e
        / \
        t   a
We say that "rgtae" is a scrambled string of "great".
Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
Source      : https://leetcode.com/problems/scramble-string/
*******************************************/
#include <stdbool.h>
bool isnScramble(char* s1, char* s2, int len)
{
    if(!strncmp(s1, s2, len)) return true;
    int count[26] = {0};
    for(int i = 0; i < len; i++) //using this method can filter almost all useless traversals;
        count[s1[i]-'a']++, count[s2[i]-'a']--;
    for(int i = 0; i < 26; i++)
        if(count[i]) return false;
    for(int i=1; i < len; i++)
        if(isnScramble(s1, s2, i) && isnScramble(s1+i, s2+i, len-i) ||
                isnScramble(s1, s2+len-i, i) && isnScramble(s1+i, s2, len-i)) return true;
    return false;
}

//AC - 0ms - beats 100% submissions;
bool isScramble1(char* s1, char* s2)
{
    int len = strlen(s1);
    return isnScramble(s1, s2, len);
}

//AC - 20ms - beats 100% submissions - DP solution;
bool isScramble(char* s1, char* s2)
{
    int len = strlen(s1);
    if(!len) return true;
    if(len==1) return *s1==*s2;
    bool*** match = (bool***)malloc(sizeof(bool**)*(len+1)); //recording the states for different length of strings starting from index 1 and index 2 respectively;
    for(int i = 0; i <= len; i++)
    {
        match[i] = (bool**)malloc(sizeof(bool*)*len);
        for(int j = 0; j < len; j++)
        {
            match[i][j] = (bool*)malloc(sizeof(bool)*len);
            memset(match[i][j], 0, sizeof(bool)*len);
        }
    }
    for(int i = 0; i < len; i++)
        for(int j = 0; j < len; j++)
            match[1][i][j] = (s1[i] == s2[j]);
    for(int size = 2; size <= len; size++)
        for(int i = 0; i <= len-size; i++)
            for(int j = 0; j <= len-size; j++)
                for(int k = 1; k<size && !match[size][i][j]; k++)
                    match[size][i][j] = (match[k][i][j] && match[size-k][i+k][j+k]) || (match[k][i+size-k][j] && match[size-k][i][j+k]);
    return match[len][0][0];
}
/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-24 09:05
Description : Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
   \       /     /      / \      \
    3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
Source      : https://leetcode.com/problems/unique-binary-search-trees-ii/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

struct TreeNode* push(struct TreeNode*** arr, int* returnSize, int a)
{
    struct TreeNode *t = NULL;
    if(a > -1) //only valid value can be allocated;
    {
        t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        t->left = t->right = NULL;
        t->val = a;
    }
    *returnSize += 1;
    *arr = (struct TreeNode**)realloc(*arr, sizeof(struct TreeNode*)*(*returnSize));
    (*arr)[*returnSize-1] = t;
    return t; //return this node for -> root;
}
struct TreeNode* generate(int begin, int end, int* returnSize)
{
    struct TreeNode** arr = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    if(begin >= end)
    {
        if(begin > end) 
            push(&arr, returnSize, -1);
        if(begin == end)
            push(&arr, returnSize, begin);
        return arr;
    }
    for(int i = begin; i <= end; i++) //try to set each value as root;
    {
        int count0=0, count1=0;
        struct TreeNode **arr0 = generate(begin, i-1, &count0);
        struct TreeNode **arr1 = generate(i+1, end, &count1);
        for(int j = 0; j < count0; j++) //try to use different node as left and right child;
            for(int k = 0; k < count1; k++)
            {
                struct TreeNode* t = push(&arr, returnSize, i);
                t->left = arr0[j];
                t->right = arr1[k];
            }
    }
    return arr;
}

//AC - 8ms;
struct TreeNode** generateTrees(int n, int* returnSize)
{
    *returnSize = 0;
    if(!n) return NULL;
    return generate(1, n, returnSize);
}
