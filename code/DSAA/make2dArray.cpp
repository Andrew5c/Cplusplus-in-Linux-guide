/*************************************************************************
	> File Name: make2dArray.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年11月06日 星期五 09时05分02秒
 ************************************************************************/

#include<iostream>
#include<exception>
#include<vector>
#include<cstdlib>
using namespace std;

// 为二维数组动态分配存储空间
template<typename T>
void make2dArray(T** &x, int numOfRow, int numOfClo) {
    // 创建行指针
    // 利用数组指针保存后面二维数组中每一行的头指针
    x = new T* [numOfRow];
    // 为每一行分配存储空间
    for(int i=0; i<numOfClo; i++){
        x[i] = new T [numOfClo];
    }
}

// 删除二维数组
template<typename T>
void delete2dArray(T** &x, int numOfRow) {
    // 删除行数组空间
    for(int i=0; i<numOfRow; i++)
        delete [] x[i];
    // 删除行指针
    delete [] x;
    x = NULL;
}

int main() {
    float **p = NULL;

    try{
        make2dArray(p, 3, 3);
    }catch(bad_alloc){
        cerr << "out of memory" << endl;
        exit(1);
    }
    // 向这个3x3的矩阵中填充数据
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            p[i][j] = i+1;
        }
    }
    cout << "p[1][1] = " << p[1][1] << endl;
    delete2dArray(p, 3);
    cout << "the 2-d array has been delete!" << endl;

    return 0;
}
