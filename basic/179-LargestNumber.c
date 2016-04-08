/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-12 21:19
Description : Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.
Source      : https://leetcode.com/problems/largest-number/
*******************************************/
#include <cstdbool.h>
#define LEN 20
//AC - 4ms;
bool compare(char* a, char* b) //if the string a+b is bigger then the string b+a return true;
{
    char *t0 = (char*)malloc(sizeof(char)*2*LEN);
    *t0 = '\0';
    strcat(t0,a);
    strcat(t0, b);
    char *t1 = (char*)malloc(sizeof(char)*LEN);
    *t1= '\0';
    strcat(t1, b);
    strcat(t1,a);
    return strcmp(t0, t1)>0; //using strcmp to achieve comparing operation;
}

int arr[] = {10000000000, 1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};
//AC - 0ms;
bool compare(int a, int b) //if the string a+b is bigger then the string b+a return true;
{
    if(!a) return 0;
    if(!b) return 1;
    long long t0=0, t1=0;
    t0 += a;
    t1 += b;
    for(int i = 0; i < 11; i++)
    {
        if(t0==a && b>=arr[i]) 
        {
            t0 *= arr[i-1];
            t0 += b;
        }
        if(t1==b && a>=arr[i])
        {
            t1 *= arr[i-1];
            t1 += a;
        }
    }
    return t0>t1;
}

char* toString(int a) //turn a int to a string;
{
    char* t = (char*)malloc(sizeof(char)*30);
    int index = 0;
    while(a) //collect each digit from low to high;
    {
        t[index++] = a%10+'0';
        a /= 10;
    }
    t[index] = '\0';
    for(int i = 0; i < index/2; i++) //reverse the string;
    {
        char c=t[i]; t[i]=t[index-i-1]; t[index-i-1]=c;
    }
    return t;
}

void sort(int* nums, int begin, int end) //to fit in the string comparison, int* should be changed to char** and int t to char* t;
{
    int l=begin, r=end;
    int v = nums[(r+l)/2];
    while(l <= r)
    {
        while(compare(v, nums[l])) l++;
        while(compare(nums[r], v)) r--;
        if(l <= r)
        {
            int t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            l++; r--;
        }
    }
    if(begin < r) sort(nums, begin, r);
    if(l < end) sort(nums, l, end);
}

//AC - using long long - 0ms - can be easily converted to string format;
char* largestNumber(int* nums, int size)
{
    char* s = (char*)malloc(sizeof(char)*size*LEN);
    *s = '\0';
    sort(nums, 0, size-1); 
    if(nums[size-1] == 0) return "0"; //if the first letter of the first number string is 0, then the result will definitely "0", just return "0";
    for(int i = size-1; i > -1; i--) //using selection sort to sort the number strings;
    strcat(s, toString(nums[i])); //collect the string from 0 to size-1 in descending order;
    return s;

}
