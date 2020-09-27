/**
* Copyright(c)
* All rights reserved.
* Author : Andrew Q.
* Date : 2020-09-11-16.00.27
* Description : ��̬�滮�����LIS����
* 1. ��������м򻯡����⻯������������״̬
* 2. �ҳ������״̬ת�Ʒ��̣����ƹ�ϵ��
*/
#include <iostream>
#include<vector>
#include<string>


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
    
    vector<int> B(arr, arr+(sizeof(arr)/sizeof(arr[0])));
    cout << LIS(A, A.size()) << endl;
    return 0;
}
