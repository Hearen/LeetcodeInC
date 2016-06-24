/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 19:22 CST
Description : There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
Source      : https://leetcode.com/problems/course-schedule/
*******************************************/
class Solution
{
private:
    bool isCycled(const vector<vector<int>>& graph, int label, vector<bool>& visited, vector<bool>& in_path)
    {
        if(visited[label]) return false; //avoid re-checking the nodes visited in previous paths; 
        visited[label] = true; //each node visited should be labelled as visited avoiding further checking;
        in_path[label] = true; //should be labelled as visited for the current path;
        for(int neighbor: graph[label])
            if(in_path[neighbor] || isCycled(graph, neighbor, visited, in_path)) return true;
        in_path[label] = false; //restored to its unvisited state for another branch of the same starting node;
        return false;
    }
public:
    //AC - 24ms - DFS method;
    bool canFinish(int num, vector<pair<int, int>> pres)
    {
        vector<vector<int>> graph(num);
        for(auto& pair: pres)
        graph[pair.second].push_back(pair.first);
        vector<bool> visited(num, false), in_path(num, false);
        for(int i = 0; i < num; i++)
            if(!visited[i] && isCycled(graph, i, visited, in_path)) return false;
        return true;
    }


    //AC - 20ms - BFS and topological sort;
    bool canFinish(int num, vector<pair<int, int>>& pres) 
    {
        vector<vector<int>> graph(num);
        vector<int> indegrees(num, 0);
        queue<int> toVisit;
        int count = 0;
        for(auto& pair: pres)
        {
            graph[pair.second].push_back(pair.first);
            indegrees[pair.first]++;
        }
        for(int i = 0; i < num; i++)
            if(!indegrees[i]) toVisit.push(i);
        while(!toVisit.empty())
        {
            int start = toVisit.front();
            toVisit.pop();
            for(auto n: graph[start])
                if(--indegrees[n] == 0) toVisit.push(n);
            count++;
        }
        return count==num;
    }
};
