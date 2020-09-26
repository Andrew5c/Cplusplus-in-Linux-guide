/*************************************************************************
	> File Name: fib.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月25日 星期五 21时21分33秒
 ************************************************************************/

#include <iostream>
#include "fib.h"

using namespace std;

// 静态数据成员类内声明，类外初始化
// 初始化时，不需要static，但是需要作用域说明
vector<int> fib::_elem;

// const修饰的函数可以修改静态成员变量
void fib::gen_elem(int pos) const
{
	// fibnicca 数列初始化
	if (fib::_elem.empty())
	{
		fib::_elem.push_back(1);
		fib::_elem.push_back(1);
	}
	for (int i = fib::_elem.size(); i < pos; i++)
	{
		fib::_elem.push_back(fib::_elem[i - 1] + fib::_elem[i - 2]);
	}
}

int fib::elem(int pos) const
{
	if (!check_integrity(pos, fib::_elem.size()))
		return 0;
	return fib::_elem[pos - 1];
}

ostream &fib::print(ostream &os) const
{
	int beg_pos = _beg_pos - 1;
	int end_pos = beg_pos + _len;
	if (end_pos > fib::_elem.size())
		fib::gen_elem(end_pos);
	os << '(' << _beg_pos << ',' << _len << ") : ";
	for (; beg_pos < end_pos; beg_pos++)
	{
		os << fib::_elem[beg_pos] << ' ';
	}
	return os;
}