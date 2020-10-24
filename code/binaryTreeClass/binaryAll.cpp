/*************************************************************************
	> File Name: binaryAll.cpp
	> Author: Andrew. Q 
	> Describe: 在一个文件中实现二叉树
	> Created Time: 2020年10月24日 星期六 10时44分04秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
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
		// 从当前二叉树中移除某一个值
        void remove_val(const valType&, btNode*&);
        // 搬移左子树到右子节点的叶子节点
        static void lchild_leaf(btNode*, btNode*);
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

template<typename valType>
void btNode<valType>::insert_val(const valType &val) {
	if(val == _val){
		_cnt++;
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



// ---------------------------------------------------
/*
 * 该类存储一个指针，指向根节点
 * 这些成员函数以reference的形式进行传递，是为了避免elemType为class类型时，
 * 产生的大量内存复制的开销
*/
template<typename elemType>
class binaryTree{
    public:
        binaryTree();
        // copy constructor 
        binaryTree(const binaryTree&);
        ~binaryTree() { clear();} 

        // 类内定义内联函数和普通类中定义一样
        bool empty() const {return _root == 0;}
        void clear() {
            if(_root){
                clear(_root);
                _root = 0;
            }
        }
        // 重载赋值运算符
        binaryTree& operator=(const binaryTree&);
        // 由最初的根节点开始插入值
        void insert(const elemType&);
        // 在树中移除某个值
        void remove(const elemType&);
        void remove_root();

        // 二叉树的前序遍历方式
        void preorder(btNode<elemType> *pt, ostream &os = cout) const;
        void preorder(ostream &os = cout) const {
            preorder(_root, os);
        }

    private:
        // 指向根节点
        btNode<elemType> *_root;
        // 复制子树
        void copy(btNode<elemType>*& tar, btNode<elemType>* src);
		// 将clear操作以重载的形式分为两个函数来进行操作
        void clear(btNode<elemType>*);
};

template<typename elemType>
inline binaryTree<elemType>::binaryTree() : _root(0) {
}

// 对于模板类，注意在类外定义其成员函数的格式
template<typename elemType>
inline binaryTree<elemType>::binaryTree(const binaryTree &rhs){
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

// 使用博文视点网站中提供的源码函数实现
template<typename elemType>
void binaryTree<elemType>::copy(btNode<elemType> *&tar, btNode<elemType> *src) {
    if(src){
        tar = new btNode<elemType>(src->_val);
        if(src->_lchild) copy(tar->_lchild, src->_lchild);
        if(src->_rchild) copy(tar->_rchild, src->_rchild);
    }
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

// ----------------------------------------------
int main() {

	binaryTree<string> bt;

    bt.insert("Piglet");
    bt.insert("Eeyore");
    bt.insert("Roo");
    bt.insert("Tigger");
    bt.insert("Chris");
    bt.insert("Pooh");
    bt.insert("Kanga");

    cout << "Preorder traversal:\n";
    bt.preorder();

    //bt.remove("Piglet");
    //cout << "\n\npreorder traversal after Piglet removal:\n";
    //bt.preorder();

    //bt.remove("Eeyore");
    //cout << "\n\nPreorder traversal after Eeyore removal:\n";
    //bt.preorder();
    //cout << endl;

	return 0;
}
