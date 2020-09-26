/*************************************************************************
	> File Name: fib.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月25日 星期五 09时23分28秒
 ************************************************************************/

#ifndef _FIB_H
#define _FIB_H

#include"num_seq.h"
#include<vector>
using namespace  std;

class fib : public num_seq{
public:
	fib(int len=1, int beg_pos=1):_beg_pos(beg_pos), _len(len), name("Fibnicca") {};
	virtual int elem(int pos) const;
	virtual const char* what_am_i() const {return name;}
	virtual ostream& print(ostream& os = cout) const;
	int length() const {return _len;}
	int beg_pos() const {return _beg_pos;}

	~fib() {};
protected:
	// 覆盖基类的纯虚函数，以自己的方式增长数列
	virtual void gen_elem(int pos) const;
	int _beg_pos;
	int _len;
	const char *name;
	static vector<int> _elem;
};

#endif
