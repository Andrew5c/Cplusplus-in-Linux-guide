#include<iostream>
using namespace std;

// 类binaryTree存储一个指针，指向根节点
// 配合其使用，让它成为当前类的friend
// 需要对其进行前置声明
template <typename elemType>
class binaryTree;

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
        const valType& value() const {return _val;}
        int occurs() const {return _cnt;}
        // 在树中插入一个值
        void insert_val(const valType&);
		// 从当前二叉树中移除某一个值
        void remove_val(const valType&, btNode*&);

		// 遍历方式
		void inorder(btNode* , ostream&) const;
		void preorder(btNode* , ostream&) const;
		void postorder(btNode* , ostream&) const;

        // 搬移左子树到右子节点的叶子节点
        static void lchild_leaf(btNode*, btNode*);
        
    private:
        // 将valType类型参数视为class类型
        // 因此，该数据成员需要参数初始化列表
        valType _val;
        // 记录节点值的重复次数
        int _cnt;
        btNode *_lchild;
        btNode *_rchild;
		// 显示当前值
        void display_val(btNode*, ostream&) const;
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
		// 找到要删除的那个值的节点
		if(_rchild) {
			// 将当前节点的父节点直接指向其右子节点，跳过当前值，就相当于删除了
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
	os << pt->_val;
	// 输出该值的个数
	if(pt->_cnt > 1)
		os << '(' << pt->_cnt << ')';
	else
		os << ' ';	
}

template<typename valType>
void btNode<valType>::inorder(btNode<valType> *pt, ostream &os) const {
    if(pt) {
		if(pt->_lchild) preorder(pt->_lchild, os);
        display_val(pt, os);
        if(pt->_rchild) preorder(pt->_rchild, os);
    }
}

template<typename valType>
void btNode<valType>::preorder(btNode<valType> *pt, ostream &os) const {
    if(pt) {
        display_val(pt, os);
        if(pt->_lchild) preorder(pt->_lchild, os);
        if(pt->_rchild) preorder(pt->_rchild, os);
    }
}

template<typename valType>
void btNode<valType>::postorder(btNode<valType> *pt, ostream &os) const {
    if(pt) {
        if(pt->_lchild) preorder(pt->_lchild, os);
        if(pt->_rchild) preorder(pt->_rchild, os);
		display_val(pt, os);
    }
}