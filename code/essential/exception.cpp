/*************************************************************************
	> File Name: exception.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年10月29日 星期四 12时26分37秒
 ************************************************************************/

#include<iostream>
using namespace std;

float devide(int num1, int num2) {
    if(num2 == 0) {
        throw "error, devisor is 0!\n";
    }else{
        return float(num1)/num2;
    }
}


int main() {
    float res;
    int num1, num2;
    cout << "pls input two nums: ";
    cin >> num1 >> num2;

    try{
        res = devide(num1, num2);
        cout << "the result is : " << res << endl;
    }
    catch(const char *msg) {
        cout << msg;
    }
    cout << "---end---" << endl;
	return 0;
}
