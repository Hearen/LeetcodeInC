### Description
In computer science, the Knuth–Morris–Pratt string searching algorithm (or KMP algorithm) searches for occurrences of a "word" W within a main "text string" S by employing the observation that when a mismatch occurs, the word itself embodies sufficient information to determine where the next match could begin, thus bypassing re-examination of previously matched characters.

The algorithm was conceived in 1970 by Donald Knuth and Vaughan Pratt, and independently by James H. Morris. The three published it jointly in 1977.

A good [reference](http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/)

### Applications

#### StrStr
```
int strStr(string haystack, string needle) {
    int nLen = needle.length(), hLen = haystack.length();
    if(nLen == 0) return 0;
    int next[nLen]{0};
    next[0] = 0;
    for(int i = 1; i < nLen; ++i) {
        int j = next[i-1];
        while(j>0 && needle[i]!=needle[j]) j = next[j-1];
        next[i] += j+(needle[i]==needle[j]); //the length of the matched prefix;
    }
    int i = 0, j = 0;
    while(i < hLen) {
        while(haystack[i]!=needle[j] && j>0) j = next[j-1];
        if(haystack[i] == needle[j]) j++;
        if(j == nLen) return i-j+1;
        i++;
    }
    return -1;
}
```

#### Palindrome
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

```
string shortestPalindrome(string s) {
    string r_s = s;
    reverse(r_s.begin(), r_s.end());
    string kmp_s = s+"#"+r_s;
    int next[kmp_s.size()]{0};
    next[0] = 0;
    for(int i = 1; i < kmp_s.length(); ++i) {
        int j = next[i-1];
        while(j>0 && kmp_s[i]!=kmp_s[j]) j = next[j-1];
        next[i] = j+(kmp_s[i]==kmp_s[j]);
    }
    return r_s.substr(0, r_s.length()-next[kmp_s.size()-1])+s;
}
```
