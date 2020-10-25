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
        binaryTree();
        // 拷贝构造函数，可以直接复制一个树到另一个树
        binaryTree(const binaryTree&);
        ~binaryTree() { clear();} 
		// 重载赋值运算符
        binaryTree& operator=(const binaryTree&);

        // 类内定义内联函数和普通类中定义一样
        bool empty() const {return _root == 0;}
        void clear() {
            if(_root){
                clear(_root);
                _root = 0;
            }
		}
        // 由最初的根节点开始插入值
        void insert(const elemType&);
        // 在树中移除某个值
        void remove(const elemType&);
        void remove_root();

        // 二叉树的前序遍历方式
        void preorder(ostream &os = *_current_os) {_root->preorder(_root, os);}
		void inorder(ostream &os = *_current_os) {_root->inorder(_root, os);}
		void postorder(ostream &os = *_current_os) {_root->postorder(_root, os);}
		
		//static ostream* os() {return _current_os;}

    private:
        // 指向根节点
        btNode<elemType> *_root;
		static ostream *_current_os;

        // 复制子树
        void copy(btNode<elemType>*& tar, btNode<elemType>* src);
		// 将clear操作以重载的形式分为两个函数来进行操作
        void clear(btNode<elemType>*);
};


#endif
