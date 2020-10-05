/*************************************************************************
	> File Name: main.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 19时11分21秒
 ************************************************************************/

#include<iostream>
#include<iterator>
#include"sort.h"

using namespace std;

int main() {
    int a[] = {11, 25, 3, 5, 10, 14};
	vector<int> vec(a, a+6);
    vector<int> res;
    Sort s(vec);

    cout << "origin num sequence : ";
    s.display(vec);
    
    if(s.bubbleSort(vec.size(), res)){
        cout << "Bubble sort result : ";
        s.display(res);
    }

    if(s.chooseSort(vec.size(), res)){
        cout << "Choose sort result : ";
        s.display(res);
    }

    if(s.quickSort()){
        cout << "Quick sort result : ";
        s.display(res);
    }
    return 0;
}
