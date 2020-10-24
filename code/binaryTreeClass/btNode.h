/*************************************************************************
	> File Name: bt.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 09时32分01秒
 ************************************************************************/

#ifndef _BTNODE_H
#define _BTNODE_H

#include<iostream>
using namespace std;

// 类binaryTree存储一个指针，指向根节点
// 配合其使用，让它成为当前类的friend
// 需要对其进行前置声明
template <typename elemType>
class binaryTree;

template <typename elemType>
class btNode;


/*
* 该类用来存储每个节点的实际值，以及连接左右两个子节点的链接
* 使用类模板实现，能够存储多种数据类型的节点
* 对于template类型参数，建议都将其视为【class类型】处理
* 因此，参数传递时需要将他们声明为const reference，而不是by value
*/
template<typename valType>
class  btNode{
    friend class binaryTree<valType>;

    public:
	    btNode(const valType &val) : _val(val) {
            _cnt = 1;
            _lchild = _rchild = 0;
        }
        ~btNode() {
            delete _lchild;
            delete _rchild;
        }
        const valType& value() const {return _val;}
        int occurs() const {return _cnt;}
        // 在树中插入一个值
        void insert_val(const valType&);
        // 搬移左子树到右子节点的叶子节点
        static void lchild_leaf(btNode*, btNode*);
        // 从当前二叉树中移除某一个值
        void remove_val(const valType&, btNode*&);
        // 显示当前值
        void display_val(btNode *pt, ostream &os = cout) const;

    private:
        // 将valType类型参数视为class类型
        // 因此，该数据成员需要参数初始化列表
        valType _val;
        // 记录节点值的重复次数
        int _cnt;
        btNode *_lchild;
        btNode *_rchild;
};

#endif
