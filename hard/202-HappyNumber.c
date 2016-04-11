/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 16:07
Description : Write an algorithm to determine if a number is "happy".
A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.
Example: 19 is a happy number
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Source      : https://leetcode.com/problems/happy-number/
*******************************************/
#include <stdbool.h>
//AC - 0ms;
//https://www.kidscodecs.com/happy-numbers/
int isHappy0(int n)
{
    int sum = 0;
    for(; n; n/=10)
        sum += (n%10)*(n%10);
    if(sum == 1)
        return true;
    int arr[] = {4, 16, 37, 58, 89, 145, 42, 20};
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
        if(sum == arr[i])
            return false;
    return isHappy(sum);
}

int squareSum(int n)
{
    int sum=0, t;
    while(n)
    {
        t = n%10;
        sum += t*t;
        n /= 10;
    }
    return sum;
}

//AC - 0ms - there must be a loop here - since the squareSum is finite while the loop is infinite;
int isHappy1(int n)
{
    int slow=n, fast=n;
    do
    {
        slow = squareSum(slow);
        fast = squareSum(fast);
        fast = squareSum(fast);
    } while(slow != fast);
    if(slow == 1) return 1;
    else return 0;
}

int isHappy2(int n)
{
    int slow=n, fast=n;
    while(slow > 1)
    {
        slow = squareSum(slow);
        if(slow == 1) return true;
        fast = squareSum(squareSum(fast));
        if(fast == 1) return true;
        if(slow == fast) return false;
    }
    return true;
}

int isHappy(int n)
{
    while(n > 6)
    {
        int next = 0;
        while(n)
        {
            next += (n%10)*(n%10);
            n /= 10;
        }
        n = next;
    }
    return n == 1;
}
