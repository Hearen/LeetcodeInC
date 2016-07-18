#include"utils.h"

int STACK[SIZE];
int INDEX;

void stackInit()
{
    INDEX = -1;
}

int pop()
{
    if(INDEX < 0)
        return -1;
    return STACK[INDEX--];
}

void push(int l, int r)
{
    if(INDEX >= SIZE - 2)
        return;
    STACK[++INDEX] = l;
    STACK[++INDEX] = r;
}

bool isEmpty()
{
    if(INDEX >= 0)
        return false;
    return true;
}

