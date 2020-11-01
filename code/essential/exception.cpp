/*************************************************************************
	> File Name: exception.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年10月29日 星期四 12时26分37秒
 ************************************************************************/

#include<iostream>
#include<exception>
#include<string>
#include<sstream>
using namespace std;

// 自定义异常类，继承标准异常
class outRange : public exception {
    public:
    outRange(int index, int max):_index(index),_max(max){

    }
    int index() {return _index;}
    int max() {return _max;}
    
    // 覆盖抽象基类中的虚函数，用来输出异常信息
    const char* what();

    private:
    int _index;
    int _max;
};

const char* outRange::what() {
    ostringstream ex_msg;
    static string msg;
    ex_msg << "The num you input out of range: "
            << _index << " exceeds maximum bound: "
            << _max;
    // 萃取出string对象
    msg = ex_msg.str();
    // 萃取出 const char* 表达式
    return msg.c_str();
}


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
    cout << "pls input two nums between 1 to 100 : ";
    cin >> num1 >> num2;

    try{
        if(num1 > 100 || num2 > 100) {
            throw outRange(num1, 100);
        }
        res = devide(num1, num2);
        cout << "the result is : " << res << endl;
    }
    catch(const char *msg) {
        cout << msg;
    }
    catch(outRange &org) {
        // 直接输出错误信息
        cout << org.what();
    }

    cout << "\n---end--- \n" << endl;
	return 0;
}
