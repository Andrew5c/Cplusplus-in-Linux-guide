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

// 书中没有实现这个函数
// 以下是笔者自己的尝试
template<typename elemType>
inline void binaryTree<elemType>::copy(btNode<elemType> *tar, btNode<elemType> *src) {
    tar->_val = src->_val;
    tar->cnt = src->cnt;
    tar->_lchild = src->_lchild;
    tar->_rchild = src->_rchild;
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

template<typename elemType>
void binaryTree<elemType>::remove_root() {
    if(!_root)
        return;
    btNode<elemType> *tmp = _root;
    if(!_root->_rchild) {
        // 右子节点存在
        // 将左子树作为右子树的叶子节点插入
        _root = _root->_rchild;
        if(tmp->_lchild) {
            // 根节点的左子树存在
            btNode<elemType> *leaf = tmp->_lchild;
            btNode<elemType> *subtree = _root->_lchild;
            if(!subtree)
                // 右子树没有任何左子节点，直接接上去
                _root->_lchild = leaf;
            else
                // 否则作为叶子节点插入
                btNode<elemType>::lchild_leaf(leaf, subtree);
        }
    }else{
        // 右子节点不存在
        // 左子节点直接变成根节点
        _root = _root->_lchild;
    }
    delete tmp;
}

template<typename elemType>
void binaryTree<elemType>::preorder(btNode<elemType> *pt, ostream &os) const {
    if(pt) {
        display_val(pt, os);
        if(pt->_lchild) preorder(pt->_lchild, os);
        if(pt->_rchild) preorder(pt->_rchild, os);
    }
}