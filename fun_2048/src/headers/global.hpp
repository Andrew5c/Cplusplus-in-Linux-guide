#ifndef __GLOBAL_H
#define __GLOBAL_H

#include<iosfwd>
#include<string>


template <typename T>
void drawAlways(std::ostream &os, T f) {
    // TODO：这里把形参直接当做函数来执行？他与函数指针有什么区别？
    os << f();
}

// 当条件满足的时候，后面就一直执行
template <typename T>
void drawOnlyWhen(std::ostream &os, bool trigger, T f) {
    if(trigger)
        drawAlways(os, f);
}

// 当条件满足的时候，仅执行一次，然后等待下一次的条件满足
template <typename T>
void drawOneTimeFlag(std::ostream &os, bool &trigger, T f) {
    if(trigger) {
        drawAlways(os, f);
        trigger = !trigger;
    }
}


// 结构体模板，保存需要的数据
template <typename suppliment_t>
struct dataSupplimentInternalType {
    suppliment_t suppliment_data;
    // TODO：重载结构体的括号运算符吗？
    template <typename function_t>
    std::string operator()(function_t f) const {
        return f(suppliment_data);
    } 
};

// TODO：这里的函数调用有必要写这么复杂吗？
// 目的是为了实现函数与参数 同时模板化？
template <typename suppliment_t, typename function_t>
auto dataSuppliment(suppliment_t data, function_t f) {
    using dsit_t = dataSupplimentInternalType<suppliment_t>;
    // 匿名函数
    const auto lambda_f_to_return = [=]() {
        // 定义一个结构体变量并初始化
        const dsit_t dataStruc = dsit_t{data};
        // 调用结构体的函数重载运算符，其参数是一个函数，用来处理自己的数据
        return dataStruc(f);
    };
    return lambda_f_to_return;
}


void cleanScreen();

#endif