#include"btNode.hpp"
using namespace std;

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

// 静态变量在类外定义
template<typename elemType>
ostream *binaryTree<elemType>::_current_os = &cout;

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
            remove_root();
        else
            _root->remove_val(val, _root); 
    }
}

template<typename elemType>
void binaryTree<elemType>::remove_root() {
    if(!_root)
        return;
    btNode<elemType> *tmp = _root;
    if(_root->_rchild) {
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
