/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-11-22.08.27
* Description : 在fibonacci函数中使用局部静态对象,避免重复计算
*/
#include<iostream>
#include<vector>
using namespace std;

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

int main(){
    const vector<int> *arr = fibo(6);
    for(int i=0; i<(*arr).size(); i++)
        cout << (*arr)[i] << ' ';
    cout << endl;
    return 0;
}


