/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 10:34
Description : Implement atoi to convert a string to an integer.
Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
Source      : https://leetcode.com/problems/string-to-integer-atoi/
*******************************************/
#include<ctype.h>
#include<limits.h>
//handle three different types octal, decimal and hexidecimal
int myAtoi0(char* s)
{
    int unit = 10;
    int index = 0;
    int size = 0;
    while(*(s+size) != '\0' && isxdigit(*(s+size)))
        size++;
    if(isdigit(*(s)))
    {
        if(*s - '0' == 0)
        {
            index = 1;
            unit = 8;
        }
        if(size > 1 && (*(s+1) == 'x' || *(s+1) == 'x'))
        {
            index = 2;  
            unit = 16;
        }
    }
    else
    {
        return 0;
    }
    int sum = 0;
    int cell = 0;
    for(; index < size; index++)
    {
        if(unit == 16)
        {
            if(isxdigit(*(s+index)))
                cell = (isalpha(*(s+index)) ? tolower(*(s+index)) - 'a' + 10 : *(s+index) - '0');
            else
                break;
        }
        else
            cell =  *(s+index) - '0';
        sum = unit * sum + cell;
    }
    return sum; 
}


//AC - 8ms
int myAtoi1(char* s)
{
    int i = 0;
    int flag = 1;
    while(isblank(*(s+i)) || isblank(*(s+i)))
        i++;
    if(*(s+i) == '-' || *(s+i) == '+')
    {
        if(*(s+i) == '-')
            flag = -1;
        i++;
    }
    long sum = 0;
    for(; isdigit(*(s+i)); i++)
    {
        sum = 10 * sum + *(s+i) - '0';
        if(sum >> 32 > 0)
            break;
    }
    sum *= flag;
    sum = sum > INT_MAX ? INT_MAX : sum;
    sum = sum < INT_MIN ? INT_MIN : sum;
    return sum;
}

//AC - 4ms - the first part should be suppresses;
int myAtoi2(char* s)
{
    int sign = 1;
    while(*s == ' ') s++; //the preceding zero can be ignored;
    if(*s == '+' || *s == '-')  //retrieve the sign;
        sign = (*s++ == '+'? 1 : -1);
    long sum = 0; //in case of INT_MAX and INT_MIN;
    while(isdigit(*s) && sum < INT_MAX) //jump out earlier if it's overflowed;
        sum = 10 * sum + (*s++ - '0');
    if(sign == 1)
        return sum > INT_MAX ? INT_MAX : sum;
    else
        return (sum *= sign) < INT_MIN ? INT_MIN : sum;
}
