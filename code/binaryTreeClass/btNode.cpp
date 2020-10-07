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
/*
* @params
* leaf : 根节点的左子树，即将被作为右子节点的叶子节点插入
* subtree : 右子节点下面的左子树
*/
template<typename valType>
void btNode<valType>::lchild_leaf(btNode *leaf, btNode *subtree) {
	// 找到右子节点中左子树的叶子节点
	while(subtree->_lchild)
		subtree = subtree->_lchild;
	// 将左子树作为叶子节点插入
	subtree->_lchild = leaf;
}

/*
* @params
* val : 需要被删除的那个值
* prev: 指向当前节点的父节点，这里使用reference to pointer的类型，是因为需要改变该pointer本身
以及它所指向的对象
*/
template<typename valType>
void btNode<valType>::remove_val(const valType &val, btNode *&prev) {
	if(val < _val) {
		if(!_lchild)
			return; // 不在这个二叉树中
		_lchild->remove_val(val, _lchild);
	}else if(val > _val) {
		if(!_rchild)
			return; // 也不在
		_rchild->remove_val(val, _rchild);
	}else {
		// 找到这个等于要删除那个值的二叉树
		if(_rchild) {
			// 将当前节点的父节点直接指向其右子节点，跳过当亲值，就相当于删除了
			prev = _rchild;
			if(_lchild) {
				if(!prev->_lchild)
					prev->_lchild = _lchild;
				else
					btNode<valType>::lchild_leaf(_lchild, prev->_lchild);
			}
		}else {
			prev = _lchild;
		}
		// 删除当前这个对象
		delete this;
	}
}

template<typename valType>
void btNode<valType>::display_val(btNode *pt, ostream &os) const {
	os << pt->_val << " ";
}