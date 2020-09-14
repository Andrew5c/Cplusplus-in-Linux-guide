/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-12-16.49.48
* Description : 动态规划法求解一个字符串中的最长回文子串
* 定义状态：p(i,j) 表示子串{s[i]...s[j]}是否回文
* 状态转移：p(i,j) = p(i+1,j-1) and s[i]==s[j]
* 边界条件：单个字符s[i]一定回文，两个字符回文时必须s[i]==s[j]
* 这种二维的动态规划，可以使用一个表格法来描述状态的变化
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

string longestPalindrome(string s)
{
    int len = s.size();
    // 记录最长回文子串的起始位置
    int start = 0;
    int maxLen = 1;
    string ans;
    // 二维数组存放每一种组合的结果
    vector<vector<bool>> dp(len, vector<bool>(len));
    // j表示子串的左边界，i右边界
    for(int j=1; j<len; j++){
        for(int i=0; i<j; i++){
            if(s[i] != s[j]){
                dp[i][j] = false;
            }else{
                if(j-i<3)
                    dp[i][j] = true;
                else
                    dp[i][j] = dp[i+1][j-1];
            }
            if(dp[i][j] && (j-i+1>maxLen)){
                maxLen = j-i+1;
                start = i;
            }
        }
    }
    // ans = s.substr(start, start+maxLen);
    int p=0;
    for(int k=start; k<k+maxLen; k++){
        ans[p] = s[k];
        p++;
    }
    return ans;
}


int main(){
    string s = "dfsdabcecbaqian";
    string ans = longestPalindrome(s);
    cout << ans << endl;

    return 0;
}
