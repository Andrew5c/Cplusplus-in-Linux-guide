/*************************************************************************
	> File Name: longestPrefix.cpp
	> Author: Andrew. Q 
	> Mail: 
	> Created Time: 2020年09月16日 星期三 19时28分29秒
 ************************************************************************/
// 寻找一组字符串vector中的最长公共前缀
#include<iostream>
#include<vector>
#include<string>

#define MIN(a, b) ((a)>(b)?(b):(a))

using namespace std;

string longestPrefix(vector<string> &strs){
    if(!strs.size())
        return "";

    int numStr = strs.size();
    // 首先得到最短的那个字符串的长度
    int lenShort = strs[0].size();
    for(int i=0; i<numStr; i++){
        lenShort = MIN(lenShort, strs[i].size());
    }
    // 记录公共前缀的长度
    int lenPrefix = 0;
    // 内部循环控制
    int j=0;
    // 最多循环numStr次，中间退出说明有不同字符
    // 那么退出时的那个循环次数就是公共前缀的字符个数
    while(lenPrefix < lenShort){
        for(; j<numStr-1; j++){
            if(strs[j][lenPrefix] == strs[j+1][lenPrefix])
                continue;
            else
                break;
        }
        // 检查是否遍历完成
        if(j == numStr-1){
            lenPrefix++;
            j = 0;
        }
        else
            break;
    }
    return strs[0].substr(0, lenPrefix);
}

int main(){
    // the longest common prefix is 'abc'
    string mystr[] = {"defg", "ab", "cklkl"};
    vector<string> strs(mystr, mystr+3);

    string res = longestPrefix(strs);

    cout << res << endl;

    return 0;
}
