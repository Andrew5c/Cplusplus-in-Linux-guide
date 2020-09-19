/*************************************************************************
	> File Name: triangular.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月18日 星期五 10时07分40秒
 ************************************************************************/

#include"Triangular.h"

vector<int> Triangular::_elems;

Triangular::Triangular(int len, int bp){
    _length = len>0?len:0;
    _beg_pos = bp>0?bp:0;
    for(int i=1; i<_length+_beg_pos; i++){
        _elems.push_back(i*(i+1)/2);
    }
}

void Triangular::gen_elems(int index) {
    for(int i=_elems.size(); i<index; i++){
        _elems.push_back(i*(i+1)/2);
    }
}

