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

bool Sort::bubbleSort(int len, vector<int> &num) {
    num.insert(num.begin(), _numVec.begin(), _numVec.end());
    if(num.empty())
        return false;
    for(int i=0; i<len-1; i++){
        for(int j=i+1; j<len; j++){
            if(num[i] > num[j])
                swap(num[i], num[j]);
        }
    }
    return true;
}


