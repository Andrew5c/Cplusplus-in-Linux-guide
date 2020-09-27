/*************************************************************************
	> File Name: num_seq.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月24日 星期四 10时40分54秒
 ************************************************************************/

#ifndef _NUM_SEQ_H
#define _NUM_SEQ_H

#include <iostream>
using namespace std;

// define an abstract class for all the sequence
class num_seq{
public:
	// 设计成虚函数，进行动态绑定
	virtual ~num_seq() {};

	// feed the value of a position
	virtual int elem(int pos) const = 0;
	// feed the name of current actual sequence
	virtual const char* what_am_i() const = 0;
	// re-write the function with RTTI
	virtual const char* what_am_i_typeid() const;
	static int max_elem() {return _max_elem;}
	// this is not a overloading, just a function named "print"
	virtual ostream& print(ostream &os = cout) const = 0;

protected:
	// 将数列的元素增长到指定的位置
	virtual void gen_elem(int pos) const = 0;
	// 检查pos是否为有效位置
	bool check_integrity(int pos, int size) const;
	const static int _max_elem = 1024;
};

// 非成员函数的形式实现output运算符重载
// 需要提前声明
ostream& operator<< (ostream &os, const num_seq &rhs);
// 使用继承体系的显示函数
void display(ostream &os, const num_seq &ns, int pos);

#endif
