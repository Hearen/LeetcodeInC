/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-05 20:48
Description : Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and  ).
Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]")"
Source      : https://leetcode.com/problems/remove-invalid-parentheses/
*******************************************/

//@s is the original string while @len is the length of it;
//@start is the start index to traverse in this round;
//@left is the count of the opening brackets not handled;
//@right is the count of the closing brackets not handled;
//@pair is used to indicate how many opening brackets contained so far which are still
//not paired by closing brackets;
//@stack is used to stored the valid characters including brackets and non-brackets while
//@top is used to index the top position in stack;
//@arr is the container for the final return value while @returnSize is the size of it;
void traverse(char* s, int len, int start, int left, int right, int pair, char* stack, int top, char*** arr, int *returnSize)
{
    if(start == len) //reach the end of the string;
    {
        if(!pair) //all brackets are closed properly then let's collect the stack;
        {
            int size = top+1;
            char *t = (char*)malloc(sizeof(char)*(size+1));
            for(int i = 0; i < size; i++)
                t[i] = stack[i];
            t[size] = '\0';
            int i = 0;
            while(i < *returnSize) //avoid duplicates;
            {
                if(!strcmp(t, (*arr)[i]))
                    break;
                i++;
            }
            if(i == *returnSize) //add a bran-new string;
            {
                *returnSize += 1;
                *arr = (char**)realloc(*arr, sizeof(char*)*(*returnSize));
                (*arr)[*returnSize-1] = t;
            }
        }
        return ;
    }
    char c = s[start];
    if(c == '(')
    {
        if(left) //try to remove it and see what might happen;
            traverse(s, len, start+1, left-1, right, pair, stack, top, arr, returnSize);
        stack[top+1] = c; //try to add it as an another opening of a pair;
        traverse(s, len, start+1, left, right, pair+1, stack, top+1, arr, returnSize);
    }
    else if(c == ')')
    {
        if(right) //try to remove it and see what will happen - since there are closing brackets left;
            traverse(s, len, start+1, left, right-1, pair, stack, top, arr, returnSize);
        if(pair) //only when there are opening brackets, we can use it as the closing half of a pair;
        {
            stack[top+1] = c;
            traverse(s, len, start+1, left, right, pair-1, stack, top+1, arr, returnSize);
        }
    }
    else //just collect since it's not brackets;
    {
        stack[top+1] = c;
        traverse(s, len, start+1, left, right, pair, stack, top+1, arr, returnSize);
    }
}

//AC - 0ms;
char** removeInvalidParentheses(char* s, int* returnSize)
{
    char** arr = (char**)malloc(sizeof(char*));
    *returnSize = 0;
    int left=0, right=0;
    for(int i = 0; s[i]; i++) //find out how many opening and closing brackets should be removed;
    {
        if(s[i] == '(') left++;
        else if(s[i] == ')')
        {
            if(left) left--;
            else right++;
        }
    }
    int len = strlen(s);
    char *stack = (char*)malloc(sizeof(char)*len);
    int top = -1;
    traverse(s, len, 0, left, right, 0, stack, top, &arr, returnSize);
    return arr;
}
