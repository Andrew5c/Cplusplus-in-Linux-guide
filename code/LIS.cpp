/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-11-16.00.27
* Description : 动态规划法求解LIS问题
* 1. 对问题进行简化、特殊化，定义出问题的状态
* 2. 找出问题的状态转移方程（递推关系）
*/
#include <iostream>
#include<vector>

using namespace std;

int LIS(const vector<int> &vec, int len)
{
    int *d = new int[len];
    int longst = 1;

    for(int i=0; i<len; i++){
        d[i] = 1;
        for(int j=0; j<i; j++){
            if(vec[j]<vec[i] && d[j]+1>d[i])
                d[i] = d[j]+1;
        }
        longst = max(longst, d[i]);
    }
    delete[] d;
    return longst;
}
int main(){
    int arr[] = {5, 3, 4, 8, 6, 7, 8};
    vector<int> A(arr, arr+(sizeof(arr)/sizeof(arr[0])));

    cout << LIS(A, A.size()) << endl;
    return 0;
}
