/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-02 16:26
Description : Given a string containing only digits, restore it by returning all possible valid IP address combinations.
For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
Source      : https://leetcode.com/problems/restore-ip-addresses/
*******************************************/
#include <stdio.h>
#include <stdlib.h>
void search(int section, char* s, int* stack, char** table, int* size)
{
    int len = strlen(s);
    if(section == 4)
    {
        int sum = stack[0] + stack[1] + stack[2] + stack[3];
        if(sum == len)
        {
            table[*size] = (char*)malloc(sizeof(char)*(len+4));
            int start = 0;
            int index = 0;
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < stack[i]; j++)
                    table[*size][index++] = s[start+j];
                start += stack[i];
                table[*size][index++] = '.';
            }
            table[*size][index-1] = '\0';
            (*size)++;
        }
        return;
    }
    int start = 0;
    for(int i = 0; i < section; i++)
        start += stack[i];
    for(int i = 1; i < 4; i++)
    {
        if(i == 2 || i == 3)
        {
            if(s[start] == '0')
                continue;
            if(i == 3)
            {
                int sum = 0;
                for(int j = 0; j < 3; j++)
                    sum = 10*sum + (s[start+j]-'0');
                if(sum > 255)
                    continue;
            }
        } 
        stack[section] = i;
        search(section+1, s, stack, table, size);
    } 
}

//AC -0ms - after removing all the 'printf' and directives;
char** restoreIpAddresses(char* s, int* size)
{
    int len = strlen(s);
    if(len > 12 || len < 4)
        return NULL;
    int stack[4] = {0};
    char** table = (char**)malloc(sizeof(char*) * 100);
    search(0, s, stack, table, size);
    return table;
}
