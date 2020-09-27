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
	const char *temp1 = f1.what_am_i_typeid();
	cout << ++temp1  << " begin at element 1 for 1 element: " << f1 << endl;

	cout << "-----------------------\n";
	
	fib f2(10, 5);
	
	cout << f2.what_am_i_typeid() << " begin at element 5 for 10 element: " << f2 << endl;

	cout << "-----------------------\n";

	display(cout, f1, 5);

	return 0;
}
