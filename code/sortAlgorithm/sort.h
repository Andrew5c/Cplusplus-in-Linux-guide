/*************************************************************************
	> File Name: sort.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 18时56分52秒
 ************************************************************************/

#ifndef _SORT_H
#define _SORT_H

#include<vector>
using namespace std;

//
class Sort{
    private:
    vector<int> _numVec;

    public:
    Sort(vector<int> a) : _numVec(a) {} ;
    
    void swap(int &, int &);
    void display(vector<int> &);
    // 冒泡排序
    // 时间 O(n2)，空间 O(1)
    bool bubbleSort(int len, vector<int>& num);
    // 选择排序
    // 时间 O(n2)，空间 O(1)
    bool chooseSort(int len, vector<int>& num);
    // 快速排序
    // 时间 O(n*log2n)，空间 O(n*log2n)
    bool quickSort(vector<int>& num, int left, int right);
};

#endif
