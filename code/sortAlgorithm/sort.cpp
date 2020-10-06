/*************************************************************************
	> File Name: sort.cpp
	> Author: Andrew. Q 
	> Describe: Some kinds of sort algorithm in c++ 
	> Created Time: 2020年09月28日 星期一 18时55分11秒
 ************************************************************************/

#include<iostream>
#include"sort.h"

void Sort::swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

void Sort::display(vector<int> &s) {
    int len = s.size();
    for(int i=0; i<len; i++ )
        cout << s[i] << ' ';
    cout << endl;
}
/*
* @param len:需要排序的数组的长度
* @param num:接收排序结果的空数组
*/
bool Sort::bubbleSort(int len, vector<int> &num) {
    num.clear();
    // 首先将数据复制到空数组，
    num.insert(num.begin(), _numVec.begin(), _numVec.end());
    if(num.empty())
        return false;
    // 开始排序
    for(int i=0; i<len-1; i++){
        for(int j=i+1; j<len; j++){
            if(num[i] > num[j])
                swap(num[i], num[j]);
        }
    }
    return true;
}

bool Sort::chooseSort(int len, vector<int> &num) {
    num.clear();
    num.insert(num.begin(), _numVec.begin(), _numVec.end());
    if(num.empty())
        return false;
    for(int i=0; i<len-1; i++) {
        // 每一轮排序中，选择第一个作为比较的对象
        int start = i;
        // 找到后面比它小的数字中最小的那一个
        for(int j=i+1; j<len; j++) {
            if(num[j] < num[start])
                start = j;
        }
        swap(num[start], num[i]);
    }
    return true;
}


bool Sort::quickSort(vector<int>& num, int left, int right) {
    num.clear();
    num.insert(num.begin(), _numVec.begin(), _numVec.end());
    if(num.empty())
        return false;



    // 分治思想，进行递归
    quickSort(num, );
    quickSort();
}