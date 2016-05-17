/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-25 16:33
Description : You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
Source      : https://leetcode.com/problems/first-bad-version/
*******************************************/
#include <stdbool.h>

bool isBadVersion(int version);

//AC - 0ms - a big warning to use low+(high-low)/2 to get mid 
//instead of (high+low)/2 which might give us overflow;
int firstBadVersion(int n)
{
    int low = 1, high = n;
    int mid;
    while(low < high)
        isBadVersion(mid = low+(high-low)/2) ? (high = mid) : (low = mid+1);
    return high;
}
