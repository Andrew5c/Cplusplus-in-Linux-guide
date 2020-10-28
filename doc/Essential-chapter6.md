# 《Essential c++》——第六章
以template进行编程

> template能够根据用户指定的特定值或者特定类型，自动产生一个函数或类。

---
## 二叉树的基本知识

- 树（tree）
    - 组成：节点（node）、连接不同节点的链接（link）

- 二叉树（binary tree）
    - 组成：左子节点、右子节点
    - 维护着每个节点与下层另两个节点间的两条链接
    - 根节点（root）：最上层第一个节点
    - 叶节点（leaf）：下面不再有任何子节点的节点

- 二叉树的遍历方式
    - 前序（preorder）：节点本身 -> 左子树 -> 右子树
    - 中序（inorder）： 左子树 -> 节点本身 -> 右子树
    - 后序（poseorder）：左子树 -> 右子树 -> 节点本身


### 指针的引用（reference to pointer）
有时我们需要用到对指针的引用来为函数传递参数，其形参如下
```
void foo(int *&p)
```
这时是因为在这个函数里面需要改变pointer本身，因此需要对指针进行引用。
如果仅仅使用pointer来传递的话，我们只能更改该pointer指向的对象，不能修改这个pointer本身。

### 拷贝构造函数 与 拷贝赋值运算符的区别？
- 拷贝构造函数和赋值运算符的行为比较相似，都是将一个对象的值复制给另一个对象；
- 拷贝构造函数使用传入对象的值生成一个新的对象的实例，而赋值运算符是将对象的值复制给一个已经存在的实例。

这种区别从两者的名字也可以很轻易的分辨出来:
- 拷贝构造函数也是一种构造函数，那么它的功能就是创建一个新的对象实例；
- 赋值运算符是执行某种运算，将一个对象的值复制给另一个对象（已经存在的）。

因此，调用的是拷贝构造函数还是赋值运算符，主要是看是否有新的对象实例产生。
- 如果产生了新的对象实例，那调用的就是拷贝构造函数；
- 如果没有，那就是对已有的对象赋值，调用的是赋值运算符。

参考这篇博客：[https://www.cnblogs.com/wangguchangqing/p/6141743.html](https://www.cnblogs.com/wangguchangqing/p/6141743.html)


### 以 function template 完成output运算符
对输出运算符的重载，也可以使用函数模板来实现，为特定的类定义输出运算符
```c++
template <typename elemType>
inline ostream& operator<<(ostream &os, const binaryTree<elemType> &bt) {
    os << "Tree : " << endl;
    bt.print(os);
    return os;
}
```
然后在需要类中将它声明为 **友元**。

### 常量表达式 与 默认参数值
注意，template参数不一定非得是某种类型（Type），也可以使用常量表达式作为template参数
```c++
template <int len, int beg_pos=1>
class num_seq{
    //...
};
```
这里的默认参数和一般函数的默认参数一样，从左到右解析。

全局作用域（global scope）内的 **函数** 及 **对象**，其地址也是一种常量表达式。
因此，也可以作为template参数，比如：
```c++
template <void (*pf) (int pos, vector<int> &seq)>
class num_seq{
    public:
    num_seq(int len, int beg_pos=1){
        if(!pf)
            //...
        pf(len+beg_pos-1, _elems)
    }
    //...

    private:
    vector<int> _elems;
};
```
这里的模板类中就可以传入某一个特定函数的地址，其调用方式为：
```c++
void fib(int pos, vector<int> &seq);
num_seq<fib> my_fib(5);  // 产生5个长度的fib数列
```

### 成员模板函数 （[代码展示](../code/essential/member_template_function.cpp)）
在非类模板中，同样可以定义一个带有template参数的成员函数，称为成员模板函数。
当然，在一个类模板中，也可以再次定义成员模板函数，构成对类参数的二次 **剥离**.


- 种种做法其实是在提高 类 的 **可复用性**
