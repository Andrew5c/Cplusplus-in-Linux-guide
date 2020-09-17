# 《Essential c++》——第四章

基于对象的编程风格

### 如何实现一个class？
- **理解**：class名称被视为一个类型（type）名称，就像内置的int、double一样。是一种自定义的、扩充的数据类型；
- class组成的两部分：一组公开的（public）操作函数和运算符（成员函数member function）； 一组私有的（private）实现细节；
- 构造函数：名称与class相同，不指定返回值，可以被重载；
	- 当class object被定义的时候，编译器自动调用构造函数对该object进行初始化；
- 析构函数：名称与class相同，前面加上`~`符号，不指定返回值，没有参数，不能重载；
	- 当object结束声明时，编译器自动调用析构函数来释放在构造函数中（或者对象声明周期中）分配的资源。

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
- 当我们以一个对象的初值作为另一个对象的初始的时候，类数据成员会被依次复制。比如：
```
Triangular tril1(8);
Triangular tril2(tril1);
```
这时，`tril1`中的值会被依次复制到`tril2`;

- 但是需要注意的是，当一个类中有**申请内存**的操作时，不能够这样进行直接初始化；
比如下面这个类的设计：
```
class Matrix{
    public:
    Matrix(int row, int col):_row(row), _col(col){
        // 进行动态内存申请
        _pmat = new double[row*col];
    }
    ~Matrix(){
        delete [] _pmat;
    }
    private:
    int _row, _col;
    double* _pmat;
}
```

> 因为这样的话，被实例化的两个对象会同时指向同一块内存，而当其中一个对象析构后，该内存就被释放，而此时另一个对象中的某个成员还在指向这块内存。这时危险的！

- 这种情况下，我们可以为这样的类提供一个**拷贝构造函数**。它的唯一参数是一个 const reference，指向自己类的对象。比如：
```
Matrix::Matrix(const Matrix &rhs)
    :_row(rhs._row), _col(rhs._col)
{
    // 拷贝构造函数实现
    int elem = _row*_col;
    _pmat = new double[elem];
    for(int i=0; i<elem; i++){
        _pmat[i] = rhs._pmat[i];
    }
}
```


#### 可变（mutable）和不变（const）
- 在成员函数的参数列表之后，紧跟一个``const``修饰符时，是为了告诉编译器，这个成员函数不会修改对象的内容；
- 如果成员函数定义在在class主体之外，那么需要在声明和定义处同时指定const；
```
class a{
    public:
    // 类内声明const
    A
    int length const {return length};
}
```
- 编译器会检查每个声明为const的成员函数。

- 如果一个类的某个私有成员变量不属于**抽象概念一环**，也就是它的改变其实不会改变不会改变这个类的状态，那么，可以用``mutable``关键字来修饰。
- 此时，可以在const成员函数中，对这种变量做出修改。

### this指针
- this指针是在成员函数内部用来指向其调用者（一个对象）的一个指针。
- 内部工作过程：这种机制的实现是因为编译器内部会自动的在每个成员函数的参数列表中加入一个名为**this**的指针。比如：
```
Triangular& Triangular::copy(const Triangular &rhs){
    // 函数实现
}
// 会被编译器修改为：
Triangular& Triangular::copy(Triangular *this, const Triangular &rhs){
    // 函数实现
}

Triangular tr1;
Triangular tr2;
tr1.copy(tr2);
// 上面这个函数会被修改为
copy(&tr1, tr2);
// 这个时候，不难理解this指针为什么会指向其调用者。
```
- 这会在我们要复制一个对象给另一个对象的时候用到。
[本节代码展示](../code/this.cpp)

### 静态（static）类成员
- 