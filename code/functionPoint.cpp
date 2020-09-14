/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-12-08.17.20
* Description : 函数指针使用联系
*/
#include<iostream>
#include<vector>
using namespace std;

/*
* 下面定义两个输出数列的函数
* 他们的返回值和参数列表相同
* 在主函数中用函数指针确定使用哪个函数
*/
const vector<int>* fibo(int num)
{
    const int MAX_SIZE = 1024;
    static vector<int> elem;

    if(num<0 || num > MAX_SIZE){
        cout << "error..." << endl;
        return 0;
    }
    for(int i=elem.size(); i<num; i++){
        if(i==0 || i==1)
            elem.push_back(1);
        else
            elem.push_back(elem[i-1]+elem[i-2]);
    }
    return &elem;
}

const vector<int>* square(int num)
{
    const int MAX_SIZE = 1024;
    static vector<int> elem;

    if(num<0 || num > MAX_SIZE){
        cout << "The num is too big or negative..." << endl;
        return 0;
    }
    for(int i=elem.size(); i<num; i++){
        elem.push_back(i*i);
    }
    return &elem;
}

/*
* 返回某种数列中指定位置的那个数
* 采用函数指针确定使用哪个函数
*/
bool seqElem(int pos, int &num, const vector<int>* (*ptr)(int)=NULL)
{
    if(ptr == NULL){
        num = 0;
        cout << "The function point to NULL...";
        return false;
    }
    const vector<int> *seq = ptr(pos);
    if(seq == NULL){
        num = 0;
        return false;
    }
    num = (*seq)[pos-1];
    return true;
}

int main(){
    // 首先定义一个函数指针数组，存放所有能用到的函数的地址（函数名）
    // 注意这个数组与普通数组定义的区别
    const vector<int>* (*funList[])(int) = {fibo, square};
    string nameList[] = {"Fibonicca", "Square"};
    enum funIndex{
        nsFibo, nsSquare
    };
    int myVal;
    const int myPos = 3;
    // 在这里可以选择自己想要使用的数列
    funIndex myIndex = nsSquare;

    if(!seqElem(myPos, myVal, funList[myIndex]))
       return 0;
    cout << "The " << nameList[myIndex] << " list in position " << myPos << " is: " \
        << myVal << endl;
    return 0;
}
