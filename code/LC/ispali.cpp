/**
* Copyright(c)
* All rights reserved.
* Author : Andrew. Q
* Date : 2020-09-11-08.29.36
* Description : 判断一个数字是否是回文数
*/
#include<iostream>
using namespace std;

bool isPalindrome(int x)
{
    if(x<0 || (x%10==0 && x!=0))
        return false;
    int pali = 0;
    while(x > pali){
        pali = pali*10 + x%10;
        x /= 10;
    }
    return (x==pali || x==(pali/10));
}


int main(){
    int num = -12321;
    cout << isPalindrome(num) << endl;
    return 0;
}
