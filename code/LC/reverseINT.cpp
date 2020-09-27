/**
* Copyright(c)
* All rights reserved.
* Author : Andrew. Q
* Date : 2020-09-10-18.32.57
* Description : 整数反转
*/
#include <iostream>

using namespace std;

int intReverse(int num)
{
    int y = 0;
    if(num/10 == 0)
        return num;

    while(num){
        // 先判断乘10之后是否会溢出
        // 因为后面需要乘10进行移位操作
        if((y*10)>=INT_MAX || (y*10)<=INT_MIN)
            return 0;
        y *= 10;
        y += num%10;
        num /= 10;
    }
    return y;
}


int main()
{
    int x = -123456;
    int y = 67890;
    cout << intReverse(x) << endl;
    cout << intReverse(y) << endl;
    return 0;
}
