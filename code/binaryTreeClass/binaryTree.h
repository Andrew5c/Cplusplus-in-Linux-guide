/*************************************************************************
	> File Name: binaryTree.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月29日 星期二 09时09分06秒
 ************************************************************************/

#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include"btNode.h"

/*
 * 该类存储一个指针，指向根节点
*/
template<typename elemType>
class binaryTree{
    public:
        binaryTree();
        // copy constructor 
        binaryTree(const binaryTree&);
        ~binaryTree();

        // 类内定义内联函数和普通类中定义一样
        bool empty() const {return _root == 0;}
        void clear();
        binaryTree& operator=(const binaryTree&);

    private:
        btNode<elemType> *_root;
        // 复制子树
        void copy(btNode<elemType>* tar, btNode<elemType>* src);
};
#endif
