/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 21:47
Description : There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].
Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
Source      : https://leetcode.com/problems/course-schedule-ii/
*******************************************/
#include <bool.h>
int* findOrder(int courses, int** prerequisites, int rSize, int cSize, int* returnSize)
{
    int* colSize = (int*)malloc(sizeof(int)*courses);
    memset(colSize, 0, sizeof(int)*courses);
    int** graph = (int**)malloc(sizeof(int*)*courses);
    for(int i = 0; i < courses; i++)
        graph[i] = (int*)malloc(sizeof(int)*10);
    for(int r = 0; r < rSize; r++)
    {
        int num = prerequisites[r][1];
        colSize[num]++;
        graph[num] = (int*)realloc(graph[num], sizeof(int)*colSize[num]);
        graph[num][colSize[num]-1] = prerequisites[r][0];
    }
    int* degrees = (int*)malloc(sizeof(int)*courses);
    memset(degrees, 0, sizeof(int)*courses);
    for(int i = 0; i < courses; i++) //retrieve the in-degree for each node in the graph represented by edge list;
        for(int j = 0; j < colSize[i]; j++)
            degrees[graph[i][j]]++;
    int *arr = (int*)malloc(sizeof(int)*courses);
    *returnSize = 0;
    while(1)
    {
        int i = 0; 
        for(; i<courses && degrees[i]!=0; i++) ; //search for a 0-in-degree node;
        if(i == courses) break; //not found - there is a cycle;
        degrees[i] = -1; //set it visited;
        for(int j = 0; j < colSize[i]; j++) degrees[graph[i][j]]--; //update all the nodes node-i pointing to;
        *returnSize += 1;
        arr[*returnSize-1] = i;
        if(*returnSize == courses) return arr;
    }
    *returnSize = 0;
    return arr;
}
