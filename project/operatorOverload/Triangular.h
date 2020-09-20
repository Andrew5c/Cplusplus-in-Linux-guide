/*************************************************************************
	> File Name: Triangular.h
	> Author: Andrew. Q
	> Describe:
	> Created Time: 2020年09月18日 星期五 08时59分39秒
 ************************************************************************/

#ifndef _TRIANGULAR_H
#define _TRIANGULAR_H

#include <vector>
using namespace std;

class Triangular_iterator{
    public:
    Triangular_iterator(int index): _index(index-1) {};
    bool operator==(const Triangular_iterator& ) const;
    bool operator!=(const Triangular_iterator& ) const;
    int operator*() const;
    Triangular_iterator& operator++();  // 前置++
    Triangular_iterator& operator++(int);  // 后置++
    void check_integrity() const;

    private:
    int _index;
};

// 此处使用的是三角数列
// 通项公式： n(n+1)/2
class Triangular{
    friend int Triangular_iterator::operator*() const;
    friend void Triangular_iterator::check_integrity() const;

    public:
    Triangular(int len=1, int bp=1){
        _length = len>0?len:0;
        _beg_pos = bp>0?bp:0;
        for(int i=1; i<_length+_beg_pos; i++){
            _elems.push_back(i*(i+1)/2);
        }
    }
    // 定义嵌套类型
    typedef Triangular_iterator iterator;
    // 实现类似迭代器的功能
    Triangular_iterator begin() const{
        return Triangular_iterator(_beg_pos);
    }
    Triangular_iterator end() const{
        return Triangular_iterator(_beg_pos+_length);
    }

    // 实现数列扩展的功能
    static void gen_elems(int index){
        for(int i=_elems.size(); i<index; i++){
            _elems.push_back(i*(i+1)/2);
        }
    }

    private:
    int _beg_pos;
    int _length;
    int _max_elems = 1024;
    static vector<int> _elems;
};
vector<int> Triangular::_elems;

// iterator的内联函数
inline bool Triangular_iterator::operator==(const Triangular_iterator& rhs) const {
    return (_index == rhs._index);
}

// 以等于运算符来实现不等
inline bool Triangular_iterator::operator!=(const Triangular_iterator& rhs) const {
    return !(*this == rhs);
}

inline int Triangular_iterator::operator*() const {
    check_integrity();
    return Triangular::_elems[_index];
}

inline Triangular_iterator& Triangular_iterator::operator++() {
    ++_index;
    check_integrity();
    return *this;
}

inline Triangular_iterator& Triangular_iterator::operator++(int) {
    Triangular_iterator tmp = *this;
    ++_index;
    check_integrity();
    return tmp;
}

inline void Triangular_iterator::check_integrity() const {
    if(_index > Triangular::_elems.size())
        Triangular::gen_elems(_index+1);
}

#endif
