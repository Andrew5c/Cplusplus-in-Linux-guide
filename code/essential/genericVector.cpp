/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-12-11.19.19
* Description : �Բ�ͬ�ķ�ʽʵ�֣���һ��vector����array�в���ĳ��ֵ
*/
#include<iostream>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include<functional>


using namespace std;

// �����ǻ�����ʵ�ַ�ʽ
// �Ժ���ģ��ֱ�ʵ�ֶ�vector��array�Ĳ���
// ������ʵ�֣�ÿ������ֻ�����vector����array
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
// �����صķ�ʽ����array�Ĳ��Һ���
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

// �����ڶԵ�һ���������г���
// ��ָ��ȡ��������Ԫ�أ��ڽ��в���
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
// ��Ϊvector�����ǿյģ�����vectorһ����������������һ��ʹ��
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

// ʹ�÷���ָ���ٴ�ʵ��find����
// ʵ�ֶ��������������͵ĸ���
template <typename iteratorType, typename elemType>
iteratorType findIterator(iteratorType first, iteratorType last, elemType &num)
{
    for(; first!=last; first++){
        if(*first == num)
            return first;
    }
    return last;
}

template <typename elemType>
void dispaly(const vector<elemType> &vec, ostream &os) {
    // 注意下面需要添加typename关键字,书中没有添加
    typename vector<elemType>::const_iterator iter_begin = vec.begin();
    typename vector<elemType>::const_iterator iter_end = vec.end();

    for(; iter_begin != iter_end; iter_begin++)
        os << *iter_begin << ' ';
    os << endl;
}

/*
- 利用泛型算法实现 统计一个容器中某个元素出现的个数
*/
int countOccurs(const vector<int> &vec, int num) {
    typename vector<int>::const_iterator iter = vec.begin();
    int num_count = 0;

    while((iter = find(iter, vec.end(), num)) != vec.end()) {
        num_count++;
        iter++; // 从当前找到的位置的下一个元素开始 新一轮的查找
    }
    return num_count;
}

/*
- 函数对象的使用
*/
vector<int> callFunctional(void) {
    vector<int> vec_a(3, 1);
    vector<int> vec_b(3, 2);
    vector<int> vec_sum(3);

    transform(vec_a.begin(), vec_a.end(), vec_b.begin(), vec_sum.begin(), plus<int>());
    return vec_sum;
}


int main(){
    int myArr[] = {1, 2, 3, 4};
    vector<int> myVec(myArr, myArr+4);

    int searchVal = 3;

    const int *ptr1 = myFind(myArr, sizeof(myArr)/sizeof(myArr[0]), searchVal);
    cout << *ptr1 << endl;
    // ʹ�����غ������в���
    const int *ptr2 = myFind(myVec, myVec.size(), searchVal);
    cout << *ptr2 << endl;

    // ---------------------------------------------
    // ���Է��ͺ���
    const int *ptr3 = myFindGeneric(myBegin(myVec), myEnd(myVec), searchVal);
    cout << *ptr3 << endl;

    const int *ptr4 = myFindGeneric(&myArr[0], &myArr[4], searchVal);
    cout << *ptr4 << endl;

    // ---------------------------------------------
    // ����iterator����ķ��ͺ���
    vector<int>::iterator ans;
    ans = findIterator(myVec.begin(), myVec.end(), searchVal);
    cout << "use the iterator fun to find vector : " << *ans << endl;

    list<int> myLs(myArr, myArr+4);
    list<int>::iterator ans2;
    ans2 = findIterator(myLs.begin(), myLs.end(), searchVal);
    cout << "use the iterator fun to find list : " << *ans2 << endl;

    // ----------
    dispaly(myVec, cout);

    // ----------
    vector<int> vec_sum = callFunctional();
    dispaly(vec_sum, cout);

    cout << countOccurs(vec_sum, 3) << endl;

    return 0;
}
