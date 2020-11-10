/*************************************************************************
	> File Name: permutation.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年11月10日 星期二 19时08分19秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<iterator>
#include<vector>
using namespace std;

// 利用递归，对一个数组中的元素进行全排列
template <typename T>
void permutation(T s[], int k, int m){
    if(k == m){
        // 将数据复制到cout，使用输出流迭代器进行输出
        copy(s, s+m+1, ostream_iterator<T> (cout, ""));
        cout << endl;
    }else{
        for(int i=k; i<=m; i++){
            swap(s[k], s[i]);
            permutation(s, k+1, m);
            swap(s[k], s[i]);
        }
    }
}


int main() {
    char s[] = {'a', 'b', 'c'};
    permutation(s, 0, 2);
	return 0;
}
