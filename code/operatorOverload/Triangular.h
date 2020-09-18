/*************************************************************************
	> File Name: Triangular.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月18日 星期五 08时59分39秒
 ************************************************************************/

#ifndef _TRIANGULAR_H
#define _TRIANGULAR_H

#include "Triangular_iterator.h"
#include<vector>

class Triangular{
    public:
    Triangular(int len=1, bp=1);
    // 定义嵌套类型
    typedef Triangular_iterator itreator;
    // 实现类似迭代器的功能
    Triangular_iterator begin() const{
        return Triangular_iterator(_beg_pos);
    }
    Triangular_iterator end() const{
        return Triangular_iterator(_beg_pos+_length)
    }
    
    // 实现数列扩展的功能
    static void gen_elems(int index);

    private:
    int _beg_pos;
    int _length;
    static int _max_elems = 1024;
    static vector<int> _elems;

friend int operator*() const;
friend void check_integrity() const;
};

inline Triangular::Triangular(int len, int bp){
    _length = len>0?len:0;
    _beg_pos = bp>0?bp:0;
}

#endif
