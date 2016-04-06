/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-17 13:52
Description : The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.
The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.
Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).
In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
-2(K)  -3  3
-5     -10 1
10     30  -5(P)
Notes:
The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
Source      : https://leetcode.com/problems/dungeon-game/
*******************************************/
#include <limits.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
//AC - 8ms;
int calculateMinimumHP0(int** dungeon, int rSize, int cSize)
{
    int** mins = (int**)malloc(sizeof(int*)*rSize);
    for(int i = 0; i < rSize; i++)
    {
        mins[i] = (int*)malloc(sizeof(int)*cSize);
        memset(mins[i], 0, sizeof(int)*cSize);
    }
    for(int i = rSize-1; i >= 0; i--)
        for(int j = cSize-1; j >= 0; j--)
        {
            if(i==rSize-1 && j==cSize-1)
                mins[i][j] = MAX(1, 1-dungeon[i][j]);
            else if(i == rSize-1)
                mins[i][j] = MAX(1, mins[i][j+1]-dungeon[i][j]);
            else if(j == cSize-1)
                mins[i][j] = MAX(1, mins[i+1][j]-dungeon[i][j]);
            else
                mins[i][j] = MAX(1, MIN(mins[i+1][j], mins[i][j+1])-dungeon[i][j]);
        }
    return mins[0][0];
}

//AC - 8ms - reduce the different conditions by adding an edge;
int calculateMinimumHP1(int** dungeon, int rSize, int cSize)
{
    int** mins = (int**)malloc(sizeof(int*)*(rSize+1));
    for(int i = 0; i <=rSize; i++)
        mins[i] = (int*)malloc(sizeof(int)*(cSize+1));
    for(int i = 0; i <= rSize; i++)
        mins[i][cSize] = INT_MAX;
    for(int i = 0; i <= cSize; i++)
        mins[rSize][i] = INT_MAX;
    mins[rSize-1][cSize] = 1; //for the very start - mins[rSize-1][cSize-1];
    mins[rSize][cSize-1] = 1;
    for(int i = rSize-1; i >= 0; i--)
        for(int j = cSize-1; j >= 0; j--)
            mins[i][j] = MAX(1, MIN(mins[i+1][j], mins[i][j+1])-dungeon[i][j]);
    return mins[0][0];
}

//AC - 8ms;
int calculateMinimumHP(int** dungeon, int rSize, int cSize)
{
    int *mins = (int*)malloc(sizeof(int)*(cSize+1));
    for(int i = 0; i <= cSize; i++)
        mins[i] = INT_MAX;
    mins[cSize-1] = 1;
    for(int i = rSize-1; i >= 0; i--)
        for(int j = cSize-1; j >= 0; j--)
            mins[j] = MAX(1, MIN(mins[j], mins[j+1])-dungeon[i][j]);
    return mins[0];
}
