/**
* Copyright(c)
* All rights reserved.
* Author : Andrew. Q
* Date : 2020-09-10-18.32.57
* Description : 一个字符串中，无重复字符最长子串的长度
*/
#include<iostream>
#include<string>
#include<unordered_set>

using namespace std;

int lengthOfLongstSubstring(string s)
{
    unordered_set<char> occ;
    int n = s.size();
    int len = 0;
    int rPoint = -1;
    for(int i=0; i<n; i++){
        if(i != 0)
            occ.erase(s[i-1]);
        while(rPoint+1<n && !occ.count(s[rPoint+1])){
            occ.insert(s[rPoint+1]);
            rPoint++;
        }
        len = max(len, rPoint-i+1);
    }
    return len;
}

int main(){
    string mystr = "abcdabcd";
    cout << lengthOfLongstSubstring(mystr) << endl;
    return 0;
}
