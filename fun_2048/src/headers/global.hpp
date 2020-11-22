#ifndef __GLOBAL_H
#define __GLOBAL_H

#include<iosfwd>
#include<string>


template <typename T>
void DrawAlways(std::ostream &os, T f) {
    // TODO：这里把形参直接当做函数来执行？
    os << f();
}

template <typename suppliment_t>
struct DataSupplimentInternalType {
    suppliment_t suppliment_data;
    // TODO：重载结构体的括号运算符吗？
    template <typename function_t>
    std::string operator()(function_t f) const {
        return f(suppliment_data);
    } 
};



void cleanScreen();

#endif