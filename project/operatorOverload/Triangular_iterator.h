/*************************************************************************
	> File Name: Triangular_iterator.h
	> Author: Andrew. Q
	> Describe:
	> Created Time: 2020年09月18日 星期五 08时49分05秒
 ************************************************************************/

#ifndef _TRIANGULAR_ITERATOR_H
#define _TRIANGULAR_ITERATOR_H

#include "Triangular.h"

using namespace std;

class Triangular;

class Triangular_iterator{
    public:
    Triangular_iterator(int index): _index(index-1) {};
    bool operator==(const Triangular_iterator& ) const;
    bool operator!=(const Triangular_iterator& ) const;
    int operator*() const;
    Triangular_iterator& operator++();  // 前置++
    Triangular_iterator& operator++(int);  // 后置++

    private:
    int _index;
    void check_integrity() const;
};

inline bool Triangular_iterator::operator==(const Triangular_iterator& rhs) const {
    return (_index == rhs._index);
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator& rhs) const {
    return (*this != rhs);
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
    // if(_index > Triangular::_max_elems)
        // throw iterator_overflow();
    //     ;
    if(_index > Triangular::_elems.size())
        Triangular::gen_elems(_index+1);
}

#endif
