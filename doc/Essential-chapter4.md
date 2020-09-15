# 《Essential c++》——第四章

基于对象的编程风格

### 如何实现一个class？
- **理解**：class名称被视为一个类型（type）名称，就像内置的int、double一样。是一种自定义的、扩充的数据类型；
- class组成的两部分：一组公开的（public）操作函数和运算符（成员函数member function）； 一组私有的（private）实现细节；
- 构造函数：名称与class相同，不指定返回值，可以被重载；
	- 当class object被定义的时候，编译器自动调用构造函数对该object进行初始化；
- 析构函数：名称与class相同，前面加上`~`符号，不指定返回值，没有参数，不能重载；
	- 当object结束声明是，编译器自动调用析构函数来释放在构造函数中（或者对象声明周期中）分配的资源。

#### 成员初始化列表
```
class Triangular{
public:
	Triangular(const Triangular &rhs);
private:
	int _length;
	int _beg;
	int _next;
}
// 采用成员初始化列表对成员变量进行初始化
Triangular::Triangular(const Triangular &rhs)
  :_length(rhs._length), _beg(rhs._beg), _next(rhs._next){}
```

#### 成员逐一初始化（拷贝构造函数）

### 