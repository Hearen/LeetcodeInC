/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-21 09:02
Description : Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
Source      : https://leetcode.com/problems/contains-duplicate-ii/
*******************************************/
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <vector.h>
//AC - 1040ms;
bool containsNearbyDuplicate0(int* nums, int size, int k)
{
    for(int i = 0; i < size; i++)
        for(int j = i+1; j < i+k+1 && j < size; j++)
            if(nums[i] == nums[j])
                return true;
    return false;
}

typedef struct hash_node
{
    int value;
    int index;
    struct hash_node *next;
} hash_node_t;


//AC - 8ms - using hash to accelerate;
bool containsNearbyDuplicate1(int* nums, int size, int k) {
    hash_node_t **table;
    table = (hash_node_t**)calloc(size, sizeof(hash_node_t));
    memset(table, 0, sizeof(hash_node_t)*size);
    int i = 0;
    int key = 0;
    hash_node_t *node, *p;
    bool result = false;
    for (i = 0; i < size; i++)
    {
        key = abs(nums[i]) % size;
        node = (hash_node_t*)malloc(sizeof(hash_node_t));
        node->value = nums[i];
        node->index = i;
        node->next = table[key];
        table[key] = node;
        p = table[key]->next;
        while(p)
        {
            if ((p->value == nums[i]) && ((i - p->index) <= k))
                return true;
            p = p->next;
        }
    }
    return false;
}

//AC -28ms - limiting the range to k by erasing the out-of-range elements;
bool containsNearbyDuplicate2(vector<int>& nums, int k) 
{
    unordered_set<int> s; 
    if (k <= 0) return false;
    if (k >= nums.size()) k = nums.size() - 1;
    for (int i = 0; i < nums.size(); i++) //make sure there are only k consecutive elements in set s;
    {
        if (i > k) s.erase(nums[i - k - 1]);
        if (s.count(nums[i])) return true;
        s.insert(nums[i]);
    }
    return false;
}

//AC - 28ms - using map to locate value and index;
bool containsNearbyDuplicate2(vector<int>& nums, int k) 
{
    unordered_map<int, int> map; 
    for (int i = 0; i < nums.size(); i++) 
    {
        if (map.count(nums[i]) && i-map[nums[i]] <= k)
        return true;
        map[nums[i]] = i; 
    }
    return false; 
}
