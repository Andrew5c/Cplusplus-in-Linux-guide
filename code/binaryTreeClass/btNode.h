/*************************************************************************
	> File Name: bt.h
	> Author: Andrew. Q 
	> Describe: 
	> Created Time: 2020年09月28日 星期一 09时32分01秒
 ************************************************************************/

#ifndef _BTNODE_H
#define _BTNODE_H

// 类binaryTree存储一个指针，指向根节点
// 配合其使用，让它成为当前类的friend
// 需要对其进行前置声明
template <typename valType>
class binaryTree;


/*
* 该类用来存储每个节点的实际值，以及连接左右两个子节点的链接
* 使用类模板实现，能够存储多种数据类型的节点
*/
template<typename valType>
class  btNode{
    friend class binaryTree;

    public:
	    btNode();
        ~btNode();

    private:
        valType _val;
        // 记录节点值的重复次数
        int cnt;
        btNode *_lchild;
        btNode *_rchild;

};

#endif
