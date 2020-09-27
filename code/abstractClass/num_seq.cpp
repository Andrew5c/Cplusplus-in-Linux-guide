/*************************************************************************
	> File Name: num_seq.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月24日 星期四 10时42分38秒
 ************************************************************************/

#include "num_seq.h"
#include<typeinfo>

ostream& operator<< (ostream &os, const num_seq &rhs){
	return rhs.print(os);
}

void display(ostream &os, const num_seq &ns, int pos){
	os << "the element at position " << pos << " for the  " << ns.what_am_i() << " is " \
	   << ns.elem(pos) << endl;
}


bool num_seq::check_integrity(int pos, int size) const {
	if(pos < 0 || pos > _max_elem){
		cerr << "!! invalid position: " << pos \
		<< ", cannot honor request \n";
		return false;
	}
	if (pos > size){
		// 这里由于多态性质，会根据调用者所属的派生类对象，来调用其相应的增长函数
		gen_elem(pos);
	}
	return true;
}

const char* num_seq::what_am_i_typeid() const {
	return typeid(*this).name();
}

