/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 15:02
Description : Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
OJ's undirected graph serialization:
Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.
The graph has a total of three nodes, and therefore contains three parts as separated by #.
First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

1
/ \
/   \
0 --- 2
    / \
    \_/
Source      : https://leetcode.com/problems/clone-graph/
*******************************************/
#include <vector.h>
#include<unordered_map>
struct UndirectedGraphNode
{
    int label;
    vector<UndirectedGraphNode*> neighbors;
    UndirectedGraphNode(int x): label(x){};
};
class Solution
{
    private: 
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> map;
        unordered_map<int, UndirectedGraphNode*> labelMap;

    public: 
        //AC - 76ms - BFS;
        UndirectedGraphNode *cloneGraph0(UndirectedGraphNode* node)
        {
            if(!node) return node;
            if(!map.count(node))
            {
                map[node] = new UndirectedGraphNode(node->label);
                for(auto&n : node->neighbors)
                map[node]->neighbors.push_back(cloneGraph(n));
            }
            return map[node];
        }

        //AC - 76ms - BFS;
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode* node)
        {
            if(!node) return node;
            if(labelMap.count(node->label))
                return labelMap[node->label];
            UndirectedGraphNode *cloned = new UndirectedGraphNode(node->label);
            labelMap[node->label] = cloned;
            for(auto& n: node->neighbors)
                cloned->neighbors.push_back(cloneGraph(n));
            return cloned;
        }
        //AC - 76ms - BFS;
        UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node)
        {
            if(!node) return node;
            UndirectedGraphNode *cloned = new UndirectedGraphNode(node->label);
            map[node] = cloned;
            queue<UndirectedGraphNode*> toVisit;
            toVisit.push(node);
            while(!toVisit.empty())
            {
                UndirectedGraphNode *cur = toVisit.pop();
                for(auto& n: cur->neighbors)
                {
                    if(!map.count(n))
                    {
                        UndirectedGraphNode *cloned = new UndirectedGraphNode(n->label);
                        map[n] = cloned;
                        toVisit.push(n);
                    }
                }
            }
            return cloned;
        }
};
