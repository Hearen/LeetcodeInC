/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-08 20:29
Description : One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
     /   \
    3     2
  / \   / \
4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.

Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.

Each comma separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".

Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true

Example 2:
"1,#"
Return false

Example 3:
"9,#,#,1"
Return false
Source      : https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
*******************************************/
#include <cstdbool.h>
//AC - 0ms - in pre-order traversal the count of null should always less than or equal to 
//that of nodes until the end -> NULLCount <= NodesCount but when reaching the end 
//NULLCount == NodesCount+1;
bool isValidSerialization0(char* preorder)
{
    int difference = 0;
    int size = strlen(preorder);
    for(int i = 1; i <= size; i++)
    {
        if(preorder[i]==',' || preorder[i]=='\0') 
        {
            if(preorder[i-1] == '#') //null;
                difference++;
            else //not null; 
                difference--;
        }
        if(difference > 1) return false; //surpass more than 1, return false directly;
        if(difference==1 && i!=size) return false; //not end of the string but it reaches difference 1 already, terminate the checking directly;
    }
    if(difference < 1) return false; //after traversing the difference should be exactly one;
    return true;
}

//AC - 0ms - using in and out degrees to check;
bool isValidSerialization(char* preorder)
{
    int difference = 1; //difference = outdegrees - indegrees;
    int len = strlen(preorder);
    for(int i = 0; i < len+1; i++)
    {
        if(preorder[i]==',' || preorder[i]=='\0')
        {
            if(--difference < 0) return false;
            if(preorder[i-1] != '#') difference += 2;
        }
    }
    return !difference;
}

