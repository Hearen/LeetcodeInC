/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-28 16:05
Description : You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:
Given nums = [5, 2, 6, 1]
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
Source      : https://leetcode.com/problems/count-of-smaller-numbers-after-self/
*******************************************/
typedef struct MyNode
{
    int val;
    int count;
    int lessCount;
    MyNode *left, *right;
    MyNode(int a): val(a), count(1), lessCount(0), left(NULL), right(NULL) {}
} Node;

class Solution 
{
private:
    void insert(Node* root, int val, int& lessCount)
    {
        int curVal = root->val;
        if(val < curVal)
        {
            root->lessCount++; //only consider the nodes inserted afterwards;
            if(!root->left) root->left = new Node(val);
            else insert(root->left, val, lessCount);
        }
        else if(val > curVal)
        {
            lessCount += root->lessCount + root->count; //using += instead of =;
            if(!root->right) root->right = new Node(val);
            else insert(root->right, val, lessCount);
        }
        else
        {
            lessCount += root->lessCount; //using += instead of =;
            root->count++;
        }
    }
public:
    //AC - 36ms - using BST to accelerate;
    vector<int> countSmaller(vector<int>& nums) 
    {
        int size = nums.size();
        if(!size) return vector<int>();
        vector<int> counters(size, 0);
        Node *root = new Node(nums[size-1]);
        for(int i = size-2; i > -1; i--)
            insert(root, nums[i], counters[i]);
        return counters;
    }
};

class Solution 
{
private:
    void merge(vector<int>& nums, int l, int r, vector<int>& index0, vector<int>& index1, vector<int>& v)
    {
        if(l == r) return ;
        int m = l+(r-l)/2;
        merge(nums, l, m, index0, index1, v);
        merge(nums, m+1, r, index0, index1, v);
        int i=l, j=m+1, k=l;
        while(i<=m || j<=r)
        {
            if((i<=m && j<=r && nums[index0[i]]<=nums[index0[j]]) || j>r)
            {
                index1[k++] = index0[i];
                v[index0[i]] += j-m-1; //how many have been collected first in the right part;
                i++;
            }
            else index1[k++] = index0[j++];
        }
        for(int i = l; i <= r; i++) index0[i] = index1[i]; //update index0 for later use;
    }
public:
    //AC - 44ms - merge sort, a stable sorting method;
    vector<int> countSmaller(vector<int>& nums) 
    {
        int size = nums.size();
        if(!size) return vector<int>();
        vector<int> index0, index1; //record the indexes of the numbers;
        for(int i = 0; i < size; i++) index0.push_back(i), index1.push_back(i);
        vector<int> v(size, 0);
        merge(nums, 0, size-1, index0, index1, v);
        return v;
    }
};
