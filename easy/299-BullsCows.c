/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 08:01
Description : You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

For example:
Secret number:  "1807"
Friend's guess: "7810"
Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)
Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".

Please note that both secret number and friend's guess may contain duplicate digits, for example:
Secret number:  "1123"
Friend's guess: "0111"
In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".
You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.
Source      : https://leetcode.com/problems/bulls-and-cows/
*******************************************/
#define LEN 1000
char* int2Str(int a, int* size)
{
    char* s = (char*)malloc(sizeof(char)*LEN);
    int index = 0;
    if(a == 0)
        s[index++] = '0';
    while(a)
    {
        s[index++] = a%10 + '0';
        a /= 10;
    }
    for(int i = 0; i < index/2; i++) //reverse the string in-position;
    {
        char t=s[i]; s[i]=s[index-i-1]; s[index-i-1]=t;
    }
    s[index] = '\0';
    *size = index;
    return s;
}

char* getHint0(char* s, char* g)
{
    int counts[10] = {0}; //count the digits in guess string which does not match in the right position;
    int bulls=0, cows=0; //count the bulls and cows;
    for(int i = 0; s[i]; i++) //count bulls, make the match digit invalid in secret and count the unmatched in guess;
    {
        if(s[i] == g[i])
        {
            s[i] = '0'-1; //make it invalid;
            bulls++;
        }
        else
            counts[g[i]-'0']++; //count the digits in guess string;
    }
    for(int i = 0; s[i]; i++) //collect the cows;
        if(isdigit(s[i]) && counts[s[i]-'0']-->0)
            cows++;
    int b=0, c=0; //make the result since the count of bulls and cows are retrieved;
    char *bStr=int2Str(bulls, &b), *cStr=int2Str(cows, &c);
    char *rStr = (char*)malloc(sizeof(char)*(b+c+3));
    *rStr = '\0';
    strcat(rStr, bStr);
    strcat(rStr, "A");
    strcat(rStr, cStr);
    strcat(rStr, "B");
    return rStr;
}

char* getHint(char* s, char* g)
{
    int counts[10] = {0}; //count the digits in guess string which does not match in the right position;
    int bulls=0, cows=0; //count the bulls and cows;
    for(int i = 0; s[i]; i++) //count bulls, make the match digit invalid in secret and count the unmatched in guess;
    {
        if(s[i] == g[i])
        {
            s[i] = '0'-1; //make it invalid;
            bulls++;
        }
        else
        {
            if(counts[s[i]-'0']++ < 0) cows++; //already appears in guess string;
            if(counts[g[i]-'0']-- > 0) cows++; //already appears in secret string;
        }
    }
    int b=0, c=0; //make the result since the count of bulls and cows are retrieved;
    char *bStr=int2Str(bulls, &b), *cStr=int2Str(cows, &c);
    char *rStr = (char*)malloc(sizeof(char)*(b+c+3));
    *rStr = '\0';
    strcat(rStr, bStr);
    strcat(rStr, "A");
    strcat(rStr, cStr);
    strcat(rStr, "B");
    return rStr;
}
