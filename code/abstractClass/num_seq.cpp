/*************************************************************************
	> File Name: num_seq.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月24日 星期四 10时42分38秒
 ************************************************************************/

#include "num_seq.h"

ostream& operator<< (ostream &os, const num_seq &rhs){
	return rhs.print(os);
}

bool num_seq::check_integrity(int pos, int size) const {
	if(pos < 0 || pos > _max_elem){
		cerr << "!! invalid position: " << pos \
		<< ", cannot honor request \n";
		return false;
	}
	if (pos > size){
		gen_elem(pos);
	}
	return true;
}
