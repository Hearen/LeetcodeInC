/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 11:15
Description : Rotate an array of n elements to the right by k steps.
For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Source      : https://leetcode.com/problems/rotate-array/
*******************************************/
void rotate0(int* nums, int size)
{
    for(int i = 0; i < size/2; i++)
    {
        int t = nums[i];
        nums[i] = nums[size-i-1];
        nums[size-i-1] = t;
    }
}
//AC - 8ms;
void rotate1(int* nums, int size, int k)
{
    k %= size;
    rotate0(nums, size);
    rotate0(nums, k);
    rotate0(nums+k, size-k);
}

void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}

//AC - 8ms;
void rotate2(int* nums, int size, int k)
{
    for(; k %= size; size-=k, nums+=k) //k should be updated to be less than or equal to the remained size;
        for(int i = 0; i < k; i++) //get the last k elements to where they should be;
            swap(nums+i, nums+size-k+i);
}

//AC - 8ms;
void rotate(int* nums, int size, int k)
{
    if(!size || !k) return ;
    int *arr = (int*)malloc(sizeof(int)*size);
    memcpy(arr, nums, sizeof(int)*size);
    for(int i = 0; i < size; i++)
        nums[(i+k)%size] = arr[i];
}
