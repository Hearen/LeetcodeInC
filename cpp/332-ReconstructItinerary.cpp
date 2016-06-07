/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-05 11:28
Description : Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
Source      : https://leetcode.com/problems/reconstruct-itinerary/
*******************************************/
#include <vector.h>
#include <string.h>
class Solution 
{
private: 
    unordered_map<string, multiset<string>> myGraph; //multiset will sort the contents;
    vector<string> route;
    void visit(string port) //DFS traversal to retrieve the route;
    {
        while(myGraph[port].size())
        {
            string next = *myGraph[port].begin(); //retrieve the next from the beginning position to ensure lexical order;
            myGraph[port].erase(myGraph[port].begin()); //once visited, erase it;
            visit(next); //move to the next;
        }
        route.push_back(port); //all edges will be covered according to the problem;
    }
public:
    //AC - 48ms;
    vector<string> findItinerary(vector<pair<string, string>> tickets)
    {
        for(auto& ticket: tickets) //constructing the graph;
            myGraph[ticket.first].insert(ticket.second);
        visit("JFK"); //start from JFK;
        return vector<string>(route.rbegin(), route.rend()); //reverse the route to the get the sequence;
    }

    //AC - 40ms;
    vector<string> findItinerary0(vector<pair<string, string>> tickets) 
    {
        unordered_map<string, multiset<string>> port_map;
        for(auto& pair: tickets)
        port_map[pair.first].insert(pair.second);
        stack<string> toVisit;
        vector<string> route;
        toVisit.push("JFK");
        while(toVisit.size())
        {
            string from = toVisit.top();
            if(port_map.count(from))
            {
                string to = *port_map[from].begin();
                toVisit.push(to);
                port_map[from].erase(port_map[from].begin());
                if(port_map[from].size() == 0) port_map.erase(from);
            }
            else
            {
                route.push_back(from);
                toVisit.pop();
            }
        }
        reverse(route.begin(), route.end());
        return route;
    }
};
