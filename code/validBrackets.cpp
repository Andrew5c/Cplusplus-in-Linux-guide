/*************************************************************************
	> File Name: validBrackets.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月22日 星期二 18时44分37秒
 ************************************************************************/

#include<iostream>
#include<string>

using namespace std;

// 判断两个参数是否匹配
#define PAIR_BRACKETS(a, b) (a=='('&&b==')'\
                             || a=='['&&b==']'\
                             || a=='{'&&b=='}')

// 检查括号的有效性
// 要么左右括号直接在一起闭合
// 要么前面的括号和后面的依照顺序依次闭合
bool isValid(string s){
    int len = s.size();
    // 奇数字符串直接排除
    if(len%2 != 0)
        return false;
    // case 1
    if(PAIR_BRACKETS(s[0], s[1])){
        for(int i=2; i<len-1; i+=2){
            if(!PAIR_BRACKETS(s[i], s[i+1])) 
                return false; 
        } 
        return true; 
    } 
    // case 2 
    else if(PAIR_BRACKETS(s[0], s[len-1])){ 
        for(int j=1; j<len/2; j++){ 
            if(!PAIR_BRACKETS(s[j], s[len-j-1])) 
            return false; 
        }
        return true; 
    }
    else{ 
        return false; 
    } 
} 


int main() {
    string s1 = "()[]{}";
    string s2 = "{([])}";
    string s3 = "[]{";
    string s4 = "[][][]";

    cout << isValid(s1) << isValid(s2) << isValid(s3) << isValid(s4) << endl;

	return 0;
}
