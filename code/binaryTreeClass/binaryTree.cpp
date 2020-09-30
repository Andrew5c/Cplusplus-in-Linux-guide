/*************************************************************************
	> File Name: binaryTree.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月29日 星期二 09时09分12秒
 ************************************************************************/

#include"binaryTree.h"
using namespace std;

// 对于模板类，注意在类外定义其成员函数的格式
template<typename elemType>
inline binaryTree<elemType>::binaryTree(const binaryTree& rhs){
    copy(_root, rhs._root);
}

template<typename elemType>
inline binaryTree<elemType>& binaryTree<elemType>::operator=(const binaryTree &rhs) {
    if(this != &rhs){
        clear();
        copy(_root, rhs._root);
    }
    return *this;
}

template<typename elemType>
inline void binaryTree<elemType>::copy(btNode<elemType> *tar, btNode<elemType> *src) {
    ;
}

// 根节点存在的情况下，递归调用的清除每一个节点
template<typename elemType>
void binaryTree<elemType>::clear(btNode<elemType> *pt) {
    // 递归调用的终止条件
    // 最后叶子节点的左右子节点为0
    if(pt){
        clear(pt->_lchild);
        clear(pt->_rchild);
        delete pt;
    }
}

template<typename elemType>
void binaryTree<elemType>::insert(const elemType &node) {
    // 没有根节点时，直接作为根节点插入
    if(!_root)
        _root = new btNode<elemType>(node);
    else
        _root->insert_val(node);
}

template<typename elemType>
void binaryTree<elemType>::remove(const elemType &val) {
    if(_root){
        // 根节点的移除做特殊处理
        if(_root->_val == val)
            _root->remove_root();
        else
            _root->remove_val(val, _root); 
    }
}