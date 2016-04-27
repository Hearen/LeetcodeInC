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
    unordered_map<string, multiset<string>> myGraph;
    vector<string> route;
    void visit(string port) //DFS traversal to retrieve the route;
    {
        //If k does not match the key of any element in the container, the function inserts a 
        //new element with that key and returns a reference to its mapped value. Notice that 
        //this always increases the container size by one, even if no mapped value is assigned 
        //to the element (the element is constructed using its default constructor).
        while(myGraph[port].size()) //the port exists in myGraph and there are others it can reach;
        {
            string next = *myGraph[port].begin(); //retrieve the next from the beginning position to ensure lexical order;
            myGraph[port].erase(myGraph[port].begin()); //once visited, erase it;
            visit(next); //move to the next;
        }
        route.push_back(port); //add the destinations first and then the source;
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
        unordered_map<string, multiset<string>> myGraph;
        int i, n = tickets.size();
        string first, second;
        for(auto &ticket: tickets) //constructing the graph;
            myGraph[ticket.first].insert(ticket.second);
        vector<string> marching;
        vector<string> itinerary;
        marching.push_back("JFK");
        while(marching.size()>0) //all tickets are to be used though there might be different lexical orders;
        {
            string from = marching.back();
            if(myGraph.count(from)) //not the final destination, push it to the stack;
            {
                multiset<string>& to = myGraph[from]; //multiset will sort the strings automatically;
                marching.push_back(*to.begin());
                to.erase(to.begin());
                if(to.empty()) myGraph.erase(from); //once the place has not any destinations more, delete it from the graph;
            }
            else
            {
                itinerary.push_back(from); //the destination - so far;
                marching.pop_back(); //delete from the stack;
            }
        }
        reverse(itinerary.begin(), itinerary.end());
        return itinerary;
    }
};
