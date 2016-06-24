/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-05 21:47
Description : For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.
Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
Example 1:
Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
0
|
1
/ \
2   3
return [1]
Example 2:
Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
0  1  2
\ | /
  3
  |
  4
  |
  5
return [3, 4]
Source      : https://leetcode.com/problems/minimum-height-trees/
*******************************************/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) 
    {
        if(n == 1) return vector<int>(1,0);
        vector<vector<int>> graph(n);
        vector<int> indegrees(n, 0);
        for(auto& pair: edges)
        {
            graph[pair.first].push_back(pair.second);
            indegrees[pair.second]++;
            graph[pair.second].push_back(pair.first);
            indegrees[pair.first]++;
        }
        int left = n; //quite essential to record the amount of nodes that still remain;
        vector<int> border0, border1; //peel the graph from the out-most border till there are only two or one nodes left;
        for(int i = 0; i < n; i++)
            if(indegrees[i] == 1) border0.push_back(i);
        while(left > 2)
        {
            for(int i = 0; i < border0.size(); i++) //peel one level at a time;
            {
                left--;
                for(int to: graph[border0[i]])
                    if(--indegrees[to] == 1) border1.push_back(to);
            }
            border0.swap(border1); //get insider;
            border1.clear();
        }
        return border0;
    }
};
