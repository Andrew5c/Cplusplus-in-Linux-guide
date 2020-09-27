/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-12-11.19.19
* Description : 以不同的方式实现，在一个vector或者array中查找某个值
*/
#include<iostream>
#include<vector>
#include<list>
#include<iterator>
using namespace std;

// 首先是基本的实现方式
// 以函数模板分别实现对vector和array的查找
// 这样的实现，每个函数只能针对vector或者array
template <typename T>
const T* myFind(const vector<T> &vec, int len, const T &num)
{
    if(vec.empty())
        return 0;
    for(int i=0; i<len; i++){
        if(vec[i] == num)
            return &vec[i];
    }
    return 0;
}
// 以重载的方式定义array的查找函数
template <typename T>
const T* myFind(const T arr[], int len, const T &num)
{
    if(!arr)
        return 0;
    for(int i=0; i<len; i++){
        if(arr[i] == num)
            return &arr[i];
    }
    return 0;
}

// 下面在对第一个参数进行抽象
// 用指针取出容器的元素，在进行操作
template <typename T>
const T* myFindGeneric(const T* start, const T* over, const T &num)
{
    if(!start || !over)
        return 0;
    for(; start!=over; start++){
        if((*start) == num)
            return start;
    }
    return 0;
}
// 因为vector可能是空的，所以vector一般配合下面这个函数一起使用
template <typename T>
inline const T* myBegin(const vector<T> &vec)
{
    return vec.empty() ? 0 : &vec[0];
}
template <typename T>
inline const T* myEnd(const vector<T> &vec)
{
    return vec.empty() ? 0 : &vec[vec.size()];
}

// 使用泛型指针再次实现find函数
// 实现对容器和数据类型的复用
template <typename iteratorType, typename elemType>
iteratorType findIterator(iteratorType first, iteratorType last, elemType &num)
{
    for(; first!=last; first++){
        if(*first == num)
            return first;
    }
    return last;
}


int main(){
    int myArr[] = {1, 2, 3, 4};
    vector<int> myVec(myArr, myArr+4);

    int searchVal = 3;

    const int *ptr1 = myFind(myArr, sizeof(myArr)/sizeof(myArr[0]), searchVal);
    cout << *ptr1 << endl;
    // 使用重载函数进行查找
    const int *ptr2 = myFind(myVec, myVec.size(), searchVal);
    cout << *ptr2 << endl;

    // ---------------------------------------------
    // 测试泛型函数
    const int *ptr3 = myFindGeneric(myBegin(myVec), myEnd(myVec), searchVal);
    cout << *ptr3 << endl;

    const int *ptr4 = myFindGeneric(&myArr[0], &myArr[4], searchVal);
    cout << *ptr4 << endl;

    // ---------------------------------------------
    // 测试iterator定义的泛型函数
    vector<int>::iterator ans;
    ans = findIterator(myVec.begin(), myVec.end(), searchVal);
    cout << "use the iterator fun to find vector : " << *ans << endl;

    list<int> myLs(myArr, myArr+4);
    list<int>::iterator ans2;
    ans2 = findIterator(myLs.begin(), myLs.end(), searchVal);
    cout << "use the iterator fun to find list : " << *ans2 << endl;

    return 0;
}
