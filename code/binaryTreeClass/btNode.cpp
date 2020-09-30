/*************************************************************************
	> File Name: btNode.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 09时32分12秒
 ************************************************************************/

#include"btNode.h"
using namespace std;


template<typename valType>
void btNode<valType>::insert_val(const valType &val) {
	if(val == _val){
		cnt++;
		return;
	}else if(val < _val){
		// 左子节点不存在时，就new一个节点出来作为左子节点
		if(!_lchild)
			_lchild = new btNode(val);
		// 左子节点存在时，以它为根节点，递归的往下插入
		else
			_lchild->insert_val(val);
	}else{
		if(!_rchild)
			_rchild = new btNode(val);
		else
			_rchild->insert_val(val);
	}
}

template<typename valType>
void btNode<valType>::remove_root() {

}


template<typename valType>
void btNode<valType>::remove_val(const valType &val, btNode<valType> *pt) {

}