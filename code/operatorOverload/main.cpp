/*************************************************************************
	> File Name: main.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月18日 星期五 10时24分26秒
 ************************************************************************/

#include<iostream>
#include"Triangular.h"
using namespace std;

int main() {
    Triangular trian(1, 8);
    Triangular::itreator it = trian.begin();
    Triangular::iterator end_it = trian.end();

    while(it != end_it){
        cout << *it << ' ';
        ++it;
    }
    cout << endl;

	return 0;
}

