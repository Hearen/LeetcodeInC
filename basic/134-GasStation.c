/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 20:42
Description : There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.
Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.
Note:
The solution is guaranteed to be unique.
Source      : https://leetcode.com/problems/gas-station/
*******************************************/
//AC - 0ms;
//https://leetcode.com/discuss/87765/clean-simple-solution-well-explained-accepted-submission
int canCompleteCircuit1(int* gas, int gSize, int* cost, int cSize)
{
    int start = gSize-1;
    int end = 0;
    int sum = gas[start]-cost[start];
    while(start > end)
    {
        if(sum >= 0) 
        {
            sum += gas[end]-cost[end];
            end++;
        }
        else 
        {
            start--;
            sum += gas[start]-cost[start]; 
        }
            
    }
    return sum >= 0? start:-1;
}
int canCompleteCircuit0(int* gas, int gSize, int* cost, int cSize)
{
    int index=-1, total=0, max=-1;
    for(int i = cSize-1; i > -1; i--)
    {
        total += gas[i]-cost[i]; //check whether the circle can be completed or not;
        if(total > max) //update the most potential index;
        {
            index=i;
            max=total;
        }
    }
    return total < 0? -1 : index;
}

