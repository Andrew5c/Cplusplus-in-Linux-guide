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
 * 这些成员函数以reference的形式进行传递，是为了避免elemType为class类型时，
 * 产生的大量内存复制的开销
*/
template<typename elemType>
class binaryTree{
    public:
        binaryTree() : _root(0) {};
        // copy constructor 
        binaryTree(const binaryTree&);
        ~binaryTree() {clear();};

        // 类内定义内联函数和普通类中定义一样
        bool empty() const {return _root == 0;}
        void clear() {
            if(_root){
                clear(_root);
                _root = 0;
            }
        }
        binaryTree& operator=(const binaryTree&);
        // 由最初的根节点开始插入值
        void insert(const elemType&);
        // 在树中移除某个值
        void remove(const elemType&);

    private:
        // 指向根节点
        btNode<elemType> *_root;
        // 复制子树
        void copy(btNode<elemType>* tar, btNode<elemType>* src);
        void clear(btNode<elemType>*);
};
#endif
