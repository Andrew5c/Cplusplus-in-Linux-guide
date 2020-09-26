/*************************************************************************
	> File Name: main.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月25日 星期五 20时41分29秒
 ************************************************************************/

#include<iostream>
#include"fib.h"

using namespace std;

int main() {
	fib f1;
	cout << f1.what_am_i()  << " begin at element 1 for 1 element: " << f1 << endl;

	cout << "-----------------------\n";
	
	fib f2(10, 5);
	cout << f2.what_am_i() << " begin at element 5 for 10 element: " << f2 << endl;
	return 0;
}
