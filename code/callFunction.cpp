/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-11-21.15.06
* Description :《Essential C++》中2.2节的代码编写
* 调用函数的不同调用方式
*/
#include<iostream>
#include<vector>
using namespace std;

// 显示函数以传址的方式进行
// 目的是为了避免对实参的复制操作，减小内存开销
// const的使用，为了可读性，并且保护参数不会被修改
void display(const vector<int> &vec)
{
    for(int i=0; i<vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}

// 这里以传址的方式进行，是为了对实参进行实际的修改
void mySwap(int &v1, int &v2)
{
    int temp = v1;
    v1 = v2;
    v2 = temp;
}
void myBubble(vector<int> &vec)
{
    int len = vec.size();
    for(int i=0; i<len; i++){
        for(int j=i+1; j<len; j++){
            if(vec[i] > vec[j])
                mySwap(vec[i], vec[j]);
        }
    }
}

// ================================================

// 以下使用 函数模板 的方法重写一遍上面的函数
// 实现可以对多种数据类型的排序
template <typename T>
void displayTemplate(const vector<T> &vec)
{
    for(int i=0; i<vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl;
}
template <typename T>
void mySwapTemplate(T &v1, T &v2)
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}
template <typename T>
void myBubbleTemplate(vector<T> &vec)
{
    int len = vec.size();
    for(int i=0; i<len; i++){
        for(int j=i+1; j<len; j++){
            if(vec[i] > vec[j])
                mySwapTemplate(vec[i], vec[j]);
        }
    }
}

int main(){
    int arr1[7] = {4, 3, 12, 45, 0, 89, 2};
    float arr2[7] = {4.5, 3.8, 12.1, 45.1, 0, 89.9, 2.3};

    vector<int> myVec1(arr1, arr1+7);
    vector<float> myVec2(arr2, arr2+7);

    cout << "vector before sorted: ";
    displayTemplate(myVec1);
    myBubbleTemplate(myVec1);
    cout << "vector after sorted: ";
    displayTemplate(myVec1);

    cout << endl << "-------------------" << endl;

    cout << "vector before sorted: ";
    displayTemplate(myVec2);
    myBubbleTemplate(myVec2);
    cout << "vector after sorted: ";
    displayTemplate(myVec2);

    return 0;
}
