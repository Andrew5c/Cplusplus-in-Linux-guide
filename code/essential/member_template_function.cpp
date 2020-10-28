/*************************************************************************
	> File Name: member_template_function.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年10月28日 星期三 10时25分38秒
 ************************************************************************/

#include<iostream>
#include<string>

using namespace std;

class printIt{
    public:
    printIt(ostream &os):_os(os) {}
    template<typename elemType>
    void print(const elemType &elem) {
        _os << elem << '\n';
    }
    private:
    ostream &_os;
};


int main() {
    printIt to_standard_out(cout);
    to_standard_out.print("hello!");
    to_standard_out.print(1234);
	
    string str("this a string");
    to_standard_out.print(str);
    return 0;
}
