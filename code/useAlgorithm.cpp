/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-13-09.19.31
* Description : 使用泛型算法完成在fibonicca数列中搜索某个值
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

// 依据vec当前的规模，向着num数值的方向增长
bool growVec(vector<int> &vec, int num)
{
    int i = vec.size();
    while(i<2){
        vec.push_back(1);
        i++;
    }
    while(vec[i-1] < num){
        vec.push_back(vec[i-1]+vec[i-2]);
        i++;
    }
    return vec[i-1]==num ? true : false;
}

bool isElem(vector<int> &vec, int num)
{
    vector<int>::iterator maxVal = max_element(vec.begin(), vec.end());
    if(*maxVal < num)
        return growVec(vec, num);

    // 二分搜索要求其作用对象要是经过排序的
    // 这里采用复制的方式，先将参数数组复制一份，在进行排序
    vector<int> vecSorted(vec.size());
    copy(vec.begin(), vec.end(), vecSorted.begin());
    sort(vecSorted.begin(), vecSorted.end());
    return binary_search(vec.begin(), vec.end(), num);
}

int main(){
    int arr[] = {1,1};
    vector<int> fibo(arr, arr+2);
    if(isElem(fibo, 8)){
        cout << "Find it..." << endl;
        return 0;
    }
    cout << "No..." << endl;
    return 0;
}
