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
    ~Sort() {_numVec.clear();}
    
    void swap(int &, int &);
    void display(vector<int> &);
    bool bubbleSort(int , vector<int>&);
   //  vector<int> chooseSort() const;
   //  vector<int> quickSort() const;
};

#endif
