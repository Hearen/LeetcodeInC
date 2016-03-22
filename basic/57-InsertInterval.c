/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 12:36
Description : Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.
Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
Source      : https://leetcode.com/problems/insert-interval/
*******************************************/
struct Interval
{
    int start;
    int end;
};

struct Interval* insert(struct Interval* intervals, int size, struct Interval newInterval, int* returnSize)
{
    size++;
    struct Interval *arr = (struct Interval*)malloc(sizeof(struct Interval)*size);
    int j = 0;
    int i = 0;
    int count=0;
    while(i < size-1) //inserting newInterval into arr with all in ascending order;
    {
        if(intervals[i].start < newInterval.start || count) // newInterval already inserted then we need to collect the remained intervals or it's bigger then we need to collect the intervals first;
            arr[i+count] = intervals[i++];
        else
            arr[i] = newInterval, count++; //inserting newInterval and counter it as a flag;
    }
    if(count == 0) arr[i] = newInterval; //make sure newInterval is not missed at the end of the intervals;
    *returnSize = 0;
    int max = 0;
    i = 0;
    while(i < size)
    {
        struct Interval t;
        t.start = arr[i].start;
        int j = i+1;
        max = arr[i].end;
        while(j<size && arr[j].start<=max) //merging intervals in arr now;
        {
            if(arr[j].end > max) max = arr[j].end;
            j++;
        }
        i = j; //update the next start index;
        t.end = max;
        *returnSize += 1;
        arr[*returnSize-1] = t; //since we are merging, arr then can be reused;
    }
    return arr;
}

