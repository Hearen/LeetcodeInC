/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-29 20:54
Description : Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.
For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Source      : https://leetcode.com/problems/integer-to-english-words/
*******************************************/
class Solution {
private:
    string recConv(int threshold[], string digit[], int num)
    {
        int i, upper, lower;
        for(i=0; num<threshold[i];++i);
        upper = num / threshold[i];
        lower = num % threshold[i];
        return (i<4? recConv(threshold, digit,upper)+" ":"")  // if the upper part is billion, million, thousand, hundred, we still need to do recursive conversion, otherwise upper=1 and no need to output
        + digit[i] + (lower? " " + recConv(threshold, digit,lower):""); // if the lower part is non zero, need to do recursive conversion
    }
public:
    string numberToWords(int num) 
    {
        int threshold[] = {1000000000, 1000000, 1000, 100, 90, 80, 70, 60,50, 40,30,20,19, 18, 17, 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
        string digit[] = {"Billion", "Million", "Thousand", "Hundred", "Ninety","Eighty", "Seventy","Sixty", "Fifty", "Forty", "Thirty", "Twenty", "Nineteen", "Eighteen", "Seventeen", "Sixteen", "Fifteen", "Fourteen", "Thirteen", "Twelve","Eleven", "Ten","Nine", "Eight", "Seven", "Six", "Five", "Four", "Three","Two", "One"};
        if(!num) return "Zero";
        return recConv(threshold, digit, num);
    }
};
