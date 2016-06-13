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
class NumArray {
private:
    int* BIT;
    int size;
    int sum(int x)
    {
        int ret = 0;
        while(x)
        {
            ret += BIT[x];
            x-= (x&-x);
        }
        return ret;
    }
public:
    NumArray(vector<int> &nums) 
    {
        size = nums.size();
        BIT = (int*)malloc(sizeof(int)*(size+1));
        memset(BIT,0,sizeof(int)*(size+1));
        for(int i = 0; i < size; i++)
        update(i,nums[i]);
    }

    void update(int i, int val) 
    {
        i++;
        val -= sum(i) - sum(i-1);
        while(i <= size)
        {
            BIT[i] += val;
            i+= (i&-i);
        }
    }
    
    //AC - 52ms - Fenwick Tree or Binary Indexed Tree;
    int sumRange(int i, int j) 
    {
        return sum(j+1) - sum(i);
    }
};

class NumArray {
private:    
    vector<long> sums;
    vector<int> nums;
    vector<pair<int,int>> buffer;
public:
    NumArray(vector<int> &nums) : sums(nums.size()+1, 0), nums(nums)
    {
        partial_sum(nums.begin(), nums.end(), sums.begin() + 1);
    }
    void update(int i, int val) 
    {
        buffer.emplace_back(i,  val - nums[i]); //buffer.push_back(make_pair(i, val-nums[i]));
        nums[i] = val;        
        if(buffer.size() > 300) 
        {
            partial_sum(nums.begin(), nums.end(), sums.begin() + 1);
            buffer.clear();
        }
    }

    //AC - 80ms - just using a buffer, dramatically reduce the time cost;
    int sumRange(int i, int j)
    {
        long result =  sums[j+1] - sums[i];
        for(const auto& p : buffer)
            if(p.first <=j && p.first >= i) result += p.second;
        return result;
    }
};


struct SegmentTreeNode 
{
    int start, end, sum;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    SegmentTreeNode(int a, int b):start(a),end(b),sum(0),left(nullptr),right(nullptr){}
};

class NumArray 
{
private:
    SegmentTreeNode* root;
    SegmentTreeNode* buildTree(vector<int> &nums, int start, int end) 
    {
        if(start > end) return nullptr;
        SegmentTreeNode* root = new SegmentTreeNode(start,end);
        if(start == end) 
        {
            root->sum = nums[start];
            return root;
        }
        int mid = start + (end - start) / 2;
        root->left = buildTree(nums,start,mid);
        root->right = buildTree(nums,mid+1,end);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }

    int modifyTree(int i, int val, SegmentTreeNode* root) 
    {
        if(root == nullptr) return 0;
        int diff;
        if(root->start == i && root->end == i) 
        {
            diff = val - root->sum;
            root->sum = val;
            return diff;
        }
        int mid = (root->start + root->end)/2;
        if(i > mid) diff = modifyTree(i,val,root->right);
        else diff = modifyTree(i,val,root->left);
        root->sum += diff;
        return diff;
    }

    int queryTree(int i, int j, SegmentTreeNode* root) 
    {
        if(root == nullptr) return 0;
        if(root->start==i && root->end==j) return root->sum;
        int mid = (root->start + root->end)/2;
        if(i > mid) return queryTree(i,j,root->right);
        if(j <= mid) return queryTree(i,j,root->left);
        return queryTree(i,mid,root->left) + queryTree(mid+1,j,root->right);
    }

public:
    NumArray(vector<int> &nums) 
    {
        root = buildTree(nums,0,nums.size()-1);
    }

    void update(int i, int val) 
    {
        modifyTree(i,val,root);
    }

    //AC - 56ms - Segment Tree;
    int sumRange(int i, int j) 
    {
        return queryTree(i, j, root);
    }
};
