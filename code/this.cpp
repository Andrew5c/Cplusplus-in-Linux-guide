/*************************************************************************
	> File Name: this.cpp
	> Author: Andrew. Q 
	> Mail: 
	> Created Time: 2020年09月16日 星期三 08时51分39秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Triangular{
    public:
    Triangular(int len=1, int bp=1);
    int length() const {return _length;}
    int beg_pos() const {return _beg_pos;}
    Triangular& copy(const Triangular &rhs);
    
    private:
    int _length;
    int _beg_pos;
};

Triangular::Triangular(int len, int bp){
    _length = len>0?len:0;
    _beg_pos = bp>0?bp:0;
}


Triangular& Triangular::copy(const Triangular &rhs) {
    // 检查两个对象是否相同
    if(this != &rhs){
        _length = rhs._length;
        _beg_pos = rhs._beg_pos;
    } 
    return *this;
} 


int main(){
    Triangular tr1(8);
    Triangular tr2(8, 9);

    cout << "tr1._length = " << tr1.length() << endl;
    cout << "tr1._beg_pos = " << tr1.beg_pos() << endl;

    tr1.copy(tr2);

    cout << "tr2._length = " << tr2.length() << endl;
    cout << "tr2._beg_pos = " << tr2.beg_pos() << endl;
    return 0;
}


