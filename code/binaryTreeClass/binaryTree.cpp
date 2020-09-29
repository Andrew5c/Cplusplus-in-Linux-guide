/*************************************************************************
	> File Name: binaryTree.cpp
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月29日 星期二 09时09分12秒
 ************************************************************************/

#include"binaryTree.h"

// 对于模板类，注意在类外定义其成员函数的格式
template<typename elemType>
inline binaryTree<elemType>::binaryTree() : _root(0) {}

template<typename elemType>
inline binaryTree<elemType>::binaryTree(const binaryTree& rhs){
    copy(_root, rhs._root);
}

template<typename elemType>
inline binaryTree<elemType>::~binaryTree() {
    clear();
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

template<typename elemType>
inline void binaryTree<elemType>::clear() {
    
}
